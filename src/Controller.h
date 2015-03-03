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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "ParkingModel.h"
#include "ParkingListModel.h"
#include "SortedParkingListModel.h"
#include "FavoritesStorage.h"
#include "JSONRequest.h"

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isRefreshing READ isRefreshing NOTIFY isRefreshingChanged)
    Q_PROPERTY(QDateTime lastUpdate READ lastUpdate NOTIFY lastUpdateChanged)

    public:
        explicit Controller(QObject *parent = 0);

        ~Controller();

        SortedParkingListModel*             model() const;
        static QHash<int, QJsonObject>      jsonArrayToHashMap(const QJsonArray &a);
        bool                                canRefresh() const;
        bool                                isRefreshing() const;
        QDateTime                           lastUpdate() const;
        Q_INVOKABLE bool                    isFavorite(const int row) const;

    private:
        static const int            refreshInterval = 180;  // Only allow refresh after 3 minutes.
        SortedParkingListModel      *m_model;
        FavoritesStorage            *m_fav;
        JSONRequest                 *m_req1;
        JSONRequest                 *m_req2;
        bool                        m_isRefreshing;
        QDateTime                   m_lastSuccessfulRefresh;

    signals:
        void    modelFilled();
        void    dataRefreshed();
        void    isRefreshingChanged();  // Needed for isRefreshing Q_PROPERTY.
        void    lastUpdateChanged();    // Needed for lastUpdate Q_PROPERTY.

    public slots:
        void        triggerUpdate();

    private slots:
        void    fillModel(const QJsonDocument &d);
        void    refresh(const QJsonDocument &d);
        void    updateData();
        void    handleNetworkError(const QNetworkReply::NetworkError &errcode);
        bool    updateFavorite(int id, bool value);
};

#endif // CONTROLLER_H
