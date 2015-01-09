#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include <QObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>

class JSONRequest : public QObject
{
    Q_OBJECT

    public:
        explicit    JSONRequest(QObject *parent = 0);
        void        request(const QString &url) const;

    private:
        QNetworkAccessManager *m_qnam;

    signals:
        void documentReady(QJsonDocument document);
        void networkError(QNetworkReply::NetworkError error);

    private slots:
        void parseJSON(QNetworkReply *reply);
};

#endif // JSONREQUEST_H
