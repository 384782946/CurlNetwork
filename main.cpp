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

    CurlNetworkReply* reply = manager.get(QUrl("https://meiban.gome.com.cn/portal/app"));
    //https://download.meixincdn.com/mxoffice/gomeplus/meiban/pro/win/Meiban_3_0_0_0.exe

//    CurlNetworkReply* reply = manager.downloadFile(
//                QUrl("https://download.meixincdn.com/mxoffice/gomeplus/meiban/pro/win/Meiban_3_0_0_0.exe")
//                ,"C:/Workspace/Projects/Meiban_3_0_0_0.exe",false);

    QEventLoop loop;

    QObject::connect(reply,&CurlNetworkReply::finished,[&](){
        if(reply->error() == 0){
            QString tmp = reply->readAll();
            qDebug() << "response:" << reply->responseStatus() << tmp;
        }else{
            qDebug() << "fail" << reply->error() << reply->errorString();
        }
        loop.exit();
    });

    //return a.exec();
}
