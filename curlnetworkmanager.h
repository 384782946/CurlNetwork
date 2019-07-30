#ifndef CURLNETWORKMANAGER_H
#define CURLNETWORKMANAGER_H

#include "curlnetwork_global.h"
#include <QUrl>
#include <QObject>
#include <QThreadPool>
#include "curlnetworkrequest.h"

class CurlNetworkReply;

class CURLNETWORKSHARED_EXPORT CurlNetworkManager:public QObject
{
public:
    CurlNetworkManager(QObject* parent = nullptr);
    ~CurlNetworkManager();

    CurlNetworkReply* get(CurlNetworkRequest request);

    CurlNetworkReply* post(CurlNetworkRequest request,const QByteArray &data);

    CurlNetworkReply* downloadFile(CurlNetworkRequest request,QString savePath,bool autoResume = true);

private:
    QThreadPool _pool;
};

#endif // CURLNETWORKMANAGER_H
