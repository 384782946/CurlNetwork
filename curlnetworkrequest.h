#ifndef CURLNETWORKREQUEST_H
#define CURLNETWORKREQUEST_H

#include "curlnetwork_global.h"

#include <QObject>
#include <QUrl>
#include <QVariant>
#include <QSharedPointer>

class CurlNetworkRequestPrivate;

class CURLNETWORKSHARED_EXPORT CurlNetworkRequest
{

//    enum KnownHeaders {
//        ContentTypeHeader,
//        ContentLengthHeader,
//        LocationHeader,
//        LastModifiedHeader,
//        CookieHeader,
//        SetCookieHeader,
//        ContentDispositionHeader,  // added for QMultipartMessage
//        UserAgentHeader,
//        ServerHeader
//    };
//    enum Attribute {
//        HttpStatusCodeAttribute,
//        HttpReasonPhraseAttribute,
//        RedirectionTargetAttribute,
//        ConnectionEncryptedAttribute,
//        CacheLoadControlAttribute,
//        CacheSaveControlAttribute,
//        SourceIsFromCacheAttribute,
//        DoNotBufferUploadDataAttribute,
//        HttpPipeliningAllowedAttribute,
//        HttpPipeliningWasUsedAttribute,
//        CustomVerbAttribute,
//        CookieLoadControlAttribute,
//        AuthenticationReuseAttribute,
//        CookieSaveControlAttribute,
//        MaximumDownloadBufferSizeAttribute, // internal
//        DownloadBufferAttribute, // internal
//        SynchronousRequestAttribute, // internal
//        BackgroundRequestAttribute,
//        SpdyAllowedAttribute,
//        SpdyWasUsedAttribute,
//        EmitAllUploadProgressSignalsAttribute,
//        FollowRedirectsAttribute,
//        HTTP2AllowedAttribute,
//        HTTP2WasUsedAttribute,
//        OriginalContentLengthAttribute,
//        RedirectPolicyAttribute,

//        User = 1000,
//        UserMax = 32767
//    };
//    enum CacheLoadControl {
//        AlwaysNetwork,
//        PreferNetwork,
//        PreferCache,
//        AlwaysCache
//    };
//    enum LoadControl {
//        Automatic = 0,
//        Manual
//    };

//    enum Priority {
//        HighPriority = 1,
//        NormalPriority = 3,
//        LowPriority = 5
//    };

//    enum RedirectPolicy {
//        ManualRedirectPolicy,
//        NoLessSafeRedirectPolicy,
//        SameOriginRedirectPolicy,
//        UserVerifiedRedirectPolicy
//    };

public:
    CurlNetworkRequest(const QUrl &url = QUrl());
    ~CurlNetworkRequest();

    bool isValid() const;

    QUrl url() const;
    void setUrl(const QUrl &url);

    // "cooked" headers
//    QVariant header(KnownHeaders header) const;
//    void setHeader(KnownHeaders header, const QVariant &value);

    // raw headers:
    bool hasRawHeader(const QByteArray &headerName) const;
    QList<QByteArray> rawHeaderList() const;
    QByteArray rawHeader(const QByteArray &headerName) const;
    void setRawHeader(const QByteArray &headerName, const QByteArray &value);

    int timeout() const;

    void setTimeout(int timeout);

    // attributes
//    QVariant attribute(Attribute code, const QVariant &defaultValue = QVariant()) const;
//    void setAttribute(Attribute code, const QVariant &value);

//    QSslConfiguration sslConfiguration() const;
//    void setSslConfiguration(const QSslConfiguration &configuration);

//    Priority priority() const;
//    void setPriority(Priority priority);

    // HTTP redirect related
    //int maximumRedirectsAllowed() const;
    //void setMaximumRedirectsAllowed(int maximumRedirectsAllowed);

private:
    QSharedPointer<CurlNetworkRequestPrivate> d;
    friend class CurlNetworkRequestPrivate;
};

#endif // CURLNETWORKREQUEST_H
