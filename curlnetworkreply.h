#ifndef CURLNETWORKREPLY_H
#define CURLNETWORKREPLY_H

#include "curlnetwork_global.h"

#include <QObject>
#include <QRunnable>
#include "curlnetworkrequest.h"

enum RequestType{
    GET,
    POST,
    DOWNLOAD,
    UPLOAD
};

class CURLNETWORKSHARED_EXPORT CurlNetworkReply:public QObject,public QRunnable
{
    Q_OBJECT
    friend class CurlNetworkManager;
public:
    CurlNetworkReply(RequestType type,const CurlNetworkRequest& request);

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

    RequestType type() const;

    QString filelocalPath() const;
    void setFilelocalPath(const QString &filelocalPath);

    bool autoResume() const;
    void setAutoResume(bool autoResume);

    QByteArray fieldData() const;
    void setFieldData(const QByteArray &fieldData);

signals:
    void finished();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

protected:
    void init_common();
    void init_get();
    void init_post();
    void init_download();
    void setErrorString(const QString &errorString);
    void debugCurlError(QString message,int eCode);

private:
    RequestType _type;
    CurlNetworkRequest _request;
    void* _curl = nullptr;
    long _responseStatus;
    std::string  _result;
    int _errorCode;
    QString _errorString;
    QByteArray _fieldData; //表单数据

    //use for upload/download file
    bool _autoResume = true; //是否断线重连
    QString _filelocalPath;
    FILE* _file = nullptr;
};

#endif // CURLNETWORKREPLY_H
