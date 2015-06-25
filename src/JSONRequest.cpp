/*
  Copyright (C) 2015 François KUBLER
  Contact: François Kubler <francois@kubler.org>
  All rights reserved.

    This file is part of StrasbourgParking.

    StrasbourgParking is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    StrasbourgParking is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "JSONRequest.h"

JSONRequest::JSONRequest(QObject *parent) :
    QObject(parent)
{
    this->m_qnam = new QNetworkAccessManager(parent);
    QObject::connect(this->m_qnam, &QNetworkAccessManager::finished, this, &JSONRequest::handleReply);
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

    reply->close();
    reply->deleteLater();
}
