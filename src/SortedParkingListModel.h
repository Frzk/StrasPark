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

#ifndef SORTEDPARKINGLISTMODEL_H
#define SORTEDPARKINGLISTMODEL_H

#include <QSortFilterProxyModel>
#include <QVariant>

#include "DataSource.h"
#include "ParkingListModel.h"

class SortedParkingListModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_ENUMS(Error)

    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
    Q_PROPERTY(bool isRefreshing READ isRefreshing NOTIFY isRefreshingChanged)
    Q_PROPERTY(QDateTime lastUpdate READ lastUpdate NOTIFY lastUpdateChanged)
    Q_PROPERTY(Error error READ error NOTIFY errorChanged)

    public:
        // Copy from ParkingListModel::Error enum
        // so that we can expose it to QML (see Q_ENUMS above).
        enum Error {
            None = ParkingListModel::None,
            Networking = ParkingListModel::Networking,
            Json = ParkingListModel::Json
        };

        explicit SortedParkingListModel();
        ~SortedParkingListModel();

        bool                            lessThan(const QModelIndex &left, const QModelIndex &right) const;
        bool                            filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

        Q_INVOKABLE void                triggerUpdate() const;
        Q_INVOKABLE void                toggleFilter();

        DataSource*                     dataSource() const;
        bool                            isRefreshing() const;
        QDateTime                       lastUpdate() const;
        SortedParkingListModel::Error   error() const;

        void                            setDataSource(DataSource*);

    signals:
        void                        dataSourceChanged();
        void                        isRefreshingChanged();
        void                        lastUpdateChanged();
        void                        errorChanged();

    private slots:
        void                        emitDataSourceChanged();
        void                        emitIsRefreshingChanged();
        void                        emitLastUpdateChanged();
        void                        emitErrorChanged();

    private:
        ParkingListModel            *m_model;
        bool                        m_filter;
};

#endif // SORTEDPARKINGLISTMODEL_H
