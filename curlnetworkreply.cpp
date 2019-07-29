#include "curlnetworkreply.h"

#include <QDebug>
#include <QFileInfo>

#include "curl/curl.h"

static char errorBuffer[1024];

int my_progress_callback(void *clientp,   double dltotal,   double dlnow,   double ultotal,   double ulnow)
{
    qDebug() << "download progress" << dltotal << dlnow;
    //    if(HttpDownloadFile::instance()->httpRequestAborted()){
    //        qDebug() << "httpRequestAborted";
    //        return 1;
    //    }
    return 0;
}

static int write_buffer(char *data,size_t size,size_t nmemb,std::string *writerData){
    unsigned long sizes = size * nmemb;
    if (writerData == NULL) return 0;
    writerData->append(data, sizes);
    return sizes;
}

static size_t write_file(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

CurlNetworkReply::CurlNetworkReply(const CurlNetworkRequest& request)
{
    _curl = curl_easy_init();

    Q_ASSERT_X(_curl,"CurlNetworkReply()","curl init error");

    _errorCode = CURLE_OK;

    _errorCode = curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, errorBuffer);

    auto url = request.url().toString().toLatin1();

    /* set URL to get here */
    _errorCode = curl_easy_setopt(_curl, CURLOPT_URL, url.data());

    /* Switch on full protocol/debug output while testing */
    _errorCode = curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, 10L);

    int timeout = request.timeout();
    if(timeout > 0){
        curl_easy_setopt(_curl, CURLOPT_TIMEOUT, (long)timeout);
    }

    _errorCode = curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA,NULL);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, 0L);

    /* SSL Options */
    _errorCode = curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    /* Provide CA Certs from http://curl.haxx.se/docs/caextract.html */
    //curl_easy_setopt(curl_handle, CURLOPT_CAINFO, "ca-bundle.crt");
}

void CurlNetworkReply::run()
{
    _responseStatus = -1;

    /* get it! */
    _errorCode = curl_easy_perform(_curl);

    if(_errorCode == CURLE_OK){
        /* get http response state */
        long retcode = 0;
        _errorCode = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE , &retcode);
        if ( _errorCode == CURLE_OK ){
            _responseStatus = retcode;
        }
    }else{
        setErrorString(errorBuffer);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(_curl);

    _curl = nullptr;

    if(_file){
        fclose(_file);
        _file = nullptr;
    }

    emit finished();
}

QByteArray CurlNetworkReply::readAll()
{
    return QByteArray::fromStdString(_result);
}

void CurlNetworkReply::init_get()
{
    _errorCode = curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 20L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION,write_buffer);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_result);
}

void CurlNetworkReply::init_post(const QByteArray& data)
{
    _errorCode = curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 20L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_POST, 1L);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_POSTFIELDS,data.data());
    _errorCode = curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION,write_buffer);
    _errorCode = curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_result);
}

void CurlNetworkReply::init_download(const QString& path,bool autoResume)
{
    auto stdPath = path.toStdString();

    if(autoResume){
        /* open the file */
        _file = fopen(stdPath.c_str(), "ab");
        if (!_file) {
            _errorCode = -1;
            setErrorString("cannot open file");
            return;
        }

        fseek(_file,0L, SEEK_END);

        //请求范围，断点续传
        QFileInfo fi(path);
        qint64 size = 0;
        if(fi.exists()){
            size = fi.size();
        }

        QString range = QString("%1-").arg(size);
        curl_easy_setopt(_curl, CURLOPT_RANGE, range.toStdString().c_str());
    }else{
        /* open the file */
        _file = fopen(stdPath.c_str(), "wb");
        if (!_file) {
            _errorCode = -1;
            setErrorString("cannot open file");
            return;
        }
    }

    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION,my_progress_callback );

    /* send all data to this function  */
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_file);

    /* write the page body to this file handle */
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _file);
}

void CurlNetworkReply::setErrorString(const QString &errorString)
{
    _errorString = errorString;
}
