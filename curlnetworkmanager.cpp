#include "curlnetworkmanager.h"

#include "curl/curl.h"
#include "curlnetworkrequest.h"
#include "curlnetworkreply.h"
#include <QDebug>
#include <QDir>

CurlNetworkManager::CurlNetworkManager(QObject* parent)
    :QObject(parent)
{
    _pool.setMaxThreadCount(10);

    curl_global_init(CURL_GLOBAL_ALL);
}

CurlNetworkManager::~CurlNetworkManager()
{
    curl_global_cleanup();
}

CurlNetworkReply* CurlNetworkManager::get(CurlNetworkRequest request)
{
    if(!request.isValid()){
        qDebug() << "CurlNetworkManager::get" << "request has invliad url";
        return nullptr;
    }

    CurlNetworkReply* reply = new CurlNetworkReply(GET,request);
    _pool.start(reply);
    return reply;
}

CurlNetworkReply* CurlNetworkManager::post(CurlNetworkRequest request,const QByteArray &data)
{
    if(!request.isValid()){
        qDebug() << "CurlNetworkManager::get" << "request has invliad url";
        return nullptr;
    }

    CurlNetworkReply* reply = new CurlNetworkReply(POST,request);
    _pool.start(reply);
    return reply;
}

CurlNetworkReply* CurlNetworkManager::downloadFile(CurlNetworkRequest request,QString savePath, bool autoResume)
{
    if(!request.isValid()){
        qDebug() << "CurlNetworkManager::get" << "request has invliad url";
        return nullptr;
    }

    CurlNetworkReply* reply = new CurlNetworkReply(DOWNLOAD,request);
    reply->setFilelocalPath(QDir::toNativeSeparators(savePath));
    reply->setAutoResume(autoResume);
    _pool.start(reply);
    return reply;
}
