#include "curlnetworkmanager.h"

#include "curl/curl.h"
#include "curlnetworkrequest.h"
#include "curlnetworkreply.h"

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

CurlNetworkReply* CurlNetworkManager::get(QUrl url)
{
    CurlNetworkRequest request(url);
    CurlNetworkReply* reply = new CurlNetworkReply(request);
    reply->init_get();
    _pool.start(reply);
    return reply;
}

CurlNetworkReply* CurlNetworkManager::post(QUrl url,const QByteArray &data)
{
    CurlNetworkRequest request(url);
    CurlNetworkReply* reply = new CurlNetworkReply(request);
    reply->init_post(data);
    _pool.start(reply);
    return reply;
}

CurlNetworkReply* CurlNetworkManager::downloadFile(QUrl url,QString savePath, bool autoResume)
{
    CurlNetworkRequest request(url);
    CurlNetworkReply* reply = new CurlNetworkReply(request);
    reply->init_download(QDir::toNativeSeparators(savePath),autoResume);
    _pool.start(reply);
    return reply;
}
