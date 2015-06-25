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

#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include <QObject>

#include <QDebug>
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
        ~JSONRequest();
        void        request(const QString &url) const;

    private:
        QNetworkAccessManager *m_qnam;

    signals:
        void documentReady(const QJsonDocument &document);
        void jsonParsingError(const QString &error);
        void networkError(const QNetworkReply::NetworkError &error);

    private slots:
        void handleReply(QNetworkReply *reply);
};

#endif // JSONREQUEST_H
