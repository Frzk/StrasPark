#include "JSONRequest.h"

JSONRequest::JSONRequest(QObject *parent) :
    QObject(parent)
{
    this->m_qnam = new QNetworkAccessManager(parent);

    QObject::connect(this->m_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleReply(QNetworkReply*)));
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
 * @emit jsonParsingError(QString error) if the data could not be parsed into a QJsonDocument.
 * @emit networkError(QNetworkReply::NetworkError error) if the request failed.
 */
void JSONRequest::handleReply(QNetworkReply *reply)
{
    QJsonParseError err;

    if(reply->error() == QNetworkReply::NoError)
    {
        QString rawData = (QString)reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(rawData.toUtf8(), &err);

        if(!doc.isNull())
            emit documentReady(doc);
        else
            emit jsonParsingError(QString("Unable to parse JSON : %1 at offset %2.").arg(err.errorString()).arg(err.offset));
    }
    else
    {
        emit networkError(reply->error());
    }

    delete reply;
}
