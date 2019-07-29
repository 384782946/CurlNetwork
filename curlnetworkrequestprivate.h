#ifndef CURLNETWORKREQUESTPRIVATE_H
#define CURLNETWORKREQUESTPRIVATE_H

#include <QMap>
#include <QByteArray>
#include <QVariant>
#include <QUrl>

class CurlNetworkRequestPrivate
{
public:
    CurlNetworkRequestPrivate();

    QUrl url;
    QMap<int,QVariant> headers;
    QMap<QByteArray,QByteArray> rawheaders;
    int timeout = 0;
};

#endif // CURLNETWORKREQUESTPRIVATE_H
