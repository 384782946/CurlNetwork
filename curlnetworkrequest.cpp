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

QVariant CurlNetworkRequest::header(CurlNetworkRequest::KnownHeaders header) const
{
    return d->headers.value((int)header);
}

void CurlNetworkRequest::setHeader(CurlNetworkRequest::KnownHeaders header, const QVariant &value)
{
    d->headers[(int)header] = value;
}

bool CurlNetworkRequest::hasRawHeader(const QByteArray &headerName) const
{
    return d->rawheaders.contains(headerName);
}

QList<QByteArray> CurlNetworkRequest::rawHeaderList() const
{
    return d->rawheaders.values();
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
