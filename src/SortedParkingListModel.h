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

#include "ParkingListModel.h"
#include "ParkingModel.h"

class SortedParkingListModel : public QSortFilterProxyModel
{
    Q_OBJECT

    public:
        // CONSTRUCTOR :
        explicit SortedParkingListModel(QObject *parent = 0);

        // DESTRUCTOR :
        ~SortedParkingListModel();

        // REIMPLEMENTED :
        bool                lessThan(const QModelIndex &left, const QModelIndex &right) const;

        // METHODS :
        ParkingListModel*   model() const;

        // Q_INVOKABLE :
        Q_INVOKABLE QVariantMap     getParking(const int row) const;

    private:
        ParkingListModel    *m_model;

    signals:
        void                favoriteChanged(int row, bool isFav);

    public slots:
        void                markAsFavorite(const int row, const bool isFav);
};

#endif // SORTEDPARKINGLISTMODEL_H
