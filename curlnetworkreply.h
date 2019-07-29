#ifndef CURLNETWORKREPLY_H
#define CURLNETWORKREPLY_H

#include "curlnetwork_global.h"

#include <QObject>
#include <QRunnable>
#include "curlnetworkrequest.h"

class CURLNETWORKSHARED_EXPORT CurlNetworkReply:public QObject,public QRunnable
{
    Q_OBJECT
    friend class CurlNetworkManager;
public:
    CurlNetworkReply(const CurlNetworkRequest& request);

    void run() override;

    int error() const {
        return _errorCode;
    }

    QByteArray readAll();

    QString errorString() const {
        return _errorString;
    }

    long responseStatus() const {
        return _responseStatus;
    }

signals:
    void finished();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

protected:
    void init_get();
    void init_post(const QByteArray& data);
    void init_download(const QString& path,bool autoResume); //是否断点重连
    void setErrorString(const QString &errorString);

private:
    void* _curl = nullptr;
    long _responseStatus;
    std::string  _result;
    int _errorCode;
    QString _errorString;

    //use for download file
    FILE* _file = nullptr;
};

#endif // CURLNETWORKREPLY_H
