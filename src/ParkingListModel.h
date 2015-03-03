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

#ifndef PARKINGLISTMODEL_H
#define PARKINGLISTMODEL_H

#include <QObject>

#include <QAbstractListModel>
#include <QNetworkAccessManager>

#include "ParkingModel.h"

class ParkingListModel : public QAbstractListModel
{
    Q_OBJECT

    // Q_PROPERTY(...)

    public:
        // CONSTRUCTOR
        explicit ParkingListModel(QObject *parent = 0);

        // DESTRUCTOR
        ~ParkingListModel();

        // CONSTANTS
        static const QString source1;
        static const QString source2;

        // REIMPLEMENTED METHODS
        int                     rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant                data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QHash<int, QByteArray>  roleNames() const;
        Qt::ItemFlags           flags(const QModelIndex &index) const;
        QModelIndex             index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

        bool                    setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        bool                    appendRow(ParkingModel *model);
        bool                    appendRows(QList<ParkingModel *> &items);
        bool                    insertRow(int row, ParkingModel *model);
        bool                    insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool                    removeRow(int row, const QModelIndex &parent = QModelIndex());
        bool                    removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
        void                    clear();

        bool                    hasIndex(int row, int column, const QModelIndex &parent) const;
        ParkingModel*           itemAt(const QModelIndex &index) const;

    signals:
        void countChanged(int);
        void isFavoriteChanged(int, bool);
        void refreshNeeded();
        void listUpToDate();

    private:
        ParkingModel            *m_prototype;
        QList<ParkingModel*>    m_parkings;
};

#endif // PARKINGLISTMODEL_H
