#include "curlnetworkrequest.h"
#include "curlnetworkrequestprivate.h"

CurlNetworkRequest::CurlNetworkRequest(const QUrl &url)
    :d(new CurlNetworkRequestPrivate)
{
    setUrl(url);
}

CurlNetworkRequest::~CurlNetworkRequest()
{

}

bool CurlNetworkRequest::isValid() const
{
    return d->url.isValid();
}

QUrl CurlNetworkRequest::url() const
{
    return d->url;
}

void CurlNetworkRequest::setUrl(const QUrl &url)
{
    if (url == d->url)
        return;

    d->url = url;
}

//QVariant CurlNetworkRequest::header(CurlNetworkRequest::KnownHeaders header) const
//{
//    return d->knownHeaders.value((int)header);
//}

//void CurlNetworkRequest::setHeader(CurlNetworkRequest::KnownHeaders header, const QVariant &value)
//{
//    d->knownHeaders[(int)header] = value;
//}

bool CurlNetworkRequest::hasRawHeader(const QByteArray &headerName) const
{
    return d->rawheaders.contains(headerName);
}

QList<QByteArray> CurlNetworkRequest::rawHeaderList() const
{
    QList<QByteArray> headers;
    foreach(auto key,d->rawheaders.keys()){
        auto v = d->rawheaders.value(key,"");
        if(!key.isEmpty() && !v.isEmpty()){
            headers.append(key + ":" + v);
        }
    }

    return headers;
}

QByteArray CurlNetworkRequest::rawHeader(const QByteArray &headerName) const
{
    return d->rawheaders.value(headerName);
}

void CurlNetworkRequest::setRawHeader(const QByteArray &headerName, const QByteArray &value)
{
    d->rawheaders[headerName] = value;
}

int CurlNetworkRequest::timeout() const
{
    return d->timeout;
}

void CurlNetworkRequest::setTimeout(int timeout)
{
    d->timeout = timeout;
}
