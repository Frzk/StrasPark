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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>

#include <QJsonDocument>

#include "JSONRequest.h"

class DataSource : public QObject
{
    Q_OBJECT

    public:
        // CONSTANTS
        static const QString source1;
        static const QString source2;

        explicit DataSource(QObject *parent = 0);

        ~DataSource();

        //Q_INVOKABLE bool                    isFavorite(const int row) const;
        void                        getList() const;
        void                        getData() const;

    private:
        JSONRequest                 *m_req1;
        JSONRequest                 *m_req2;

    signals:
        void    listReady(const QJsonDocument &d);
        void    dataReady(const QJsonDocument &d);
        void    networkError(const QNetworkReply::NetworkError &errcode);

    private slots:
        void    emitListReady(const QJsonDocument &d);
        void    emitDataReady(const QJsonDocument &d);
        void    emitNetworkError(const QNetworkReply::NetworkError &errcode);
};

#endif // CONTROLLER_H
