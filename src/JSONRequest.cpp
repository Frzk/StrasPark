#include "JSONRequest.h"

JSONRequest::JSONRequest(QObject *parent) :
    QObject(parent)
{
    this->m_qnam = new QNetworkAccessManager(parent);

    QObject::connect(this->m_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseJSON(QNetworkReply*)));
}

JSONRequest::~JSONRequest()
{
    delete this->m_qnam;
}

/**
 * @brief Launch a GET HTTP request to the given url.
 *
 * Note that a JSON response is expected.
 * The request is asynchronous : parseJSON will be called once the request is finished, thanks to the signal/slot mechanism.
 *
 * @param   url URL of the service
 */
void JSONRequest::request(const QString &url) const
{
    QUrl source = QUrl(url);
    QNetworkRequest request = QNetworkRequest(source);

    this->m_qnam->get(request);
}

/**
 * @brief Checks if the request succeeded, and, if it did, tries to parse the data as JSON.
 *
 * @param   reply   Reply received from the QNetworkAccessManager (we expect it to be a valid JSON document).
 *
 * @emit documentReady(QJsonDocument document) if the request succeeded and the document has been parsed successfully.
 * @emit networkError(QNetworkReply::NetworkError error) if the request failed.
 */
void JSONRequest::parseJSON(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QString rawData = (QString)reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(rawData.toUtf8());

        emit documentReady(doc);
    }
    else
    {
        emit networkError(reply->error());
    }

    delete reply;
}
