#include <QCoreApplication>

#include <QDebug>
#include <QEventLoop>
#include <QMetaObject>
#include "curlnetworkmanager.h"
#include "curlnetworkreply.h"
#include "curlnetworkrequest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CurlNetworkManager manager;
    CurlNetworkReply* reply = manager.get(QUrl("http://meiban.gome.com.cn/portal"));
    //https://download.meixincdn.com/mxoffice/gomeplus/meiban/pro/win/Meiban_3_0_0_0.exe

//    CurlNetworkRequest request(QUrl("https://download.meixincdn.com/mxoffice/gomeplus/meiban/pro/win/Meiban_3_0_0_0.exe"));
//    request.setRawHeader("user-agent","Mozilla/5.0");
//    CurlNetworkReply* reply = manager.downloadFile(
//                request
//                ,"C:/Workspace/Projects/Meiban_3_0_0_0.exe"
//                ,false);

    QEventLoop loop;
    QObject::connect(reply,&CurlNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exit();

    if(reply->error() == 0){
        QString tmp = reply->readAll();
        qDebug() << "response:" << reply->responseStatus() << tmp;
    }else{
        qDebug() << "fail" << reply->error() << reply->errorString();
    }

    return 0;
}
