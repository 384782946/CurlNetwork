#ifndef CURLNETWORKMANAGER_H
#define CURLNETWORKMANAGER_H

#include "curlnetwork_global.h"
#include <QUrl>
#include <QObject>
#include <QThreadPool>

class CurlNetworkReply;

class CURLNETWORKSHARED_EXPORT CurlNetworkManager:public QObject
{
public:
    CurlNetworkManager(QObject* parent = nullptr);
    ~CurlNetworkManager();

    CurlNetworkReply* get(QUrl url);

    CurlNetworkReply* post(QUrl url,const QByteArray &data);

    CurlNetworkReply* downloadFile(QUrl url,QString savePath,bool autoResume = true);

private:
    QThreadPool _pool;
};

#endif // CURLNETWORKMANAGER_H
