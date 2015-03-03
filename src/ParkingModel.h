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

#ifndef PARKINGMODEL_H
#define PARKINGMODEL_H

#include <QObject>

#include <QDebug>
#include <QHash>
#include <QString>
#include <QVariant>

class ParkingModel : public QObject
{
    Q_OBJECT

    public:
        explicit ParkingModel(QObject *parent = 0);
        explicit ParkingModel(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite, QObject *parent = 0);
        ParkingModel(const ParkingModel &park, QObject *parent = 0);

        ~ParkingModel();

        bool                    operator<(const ParkingModel &other) const;

        int                     getId() const;
        QString                 getName() const;
        QString                 getStatus() const;
        QString                 getLongitude() const;
        QString                 getLatitude() const;
        int                     getFree() const;
        int                     getTotal() const;
        bool                    getIsRelay() const;
        bool                    getIsFavorite() const;

        void                    setId(const QVariant &id);
        void                    setName(const QVariant &name);
        void                    setStatus(const QVariant &status);
        void                    setLongitude(const QVariant &lng);
        void                    setLatitude(const QVariant &lat);
        void                    setFree(const QVariant &freep);
        void                    setTotal(const QVariant &total);
        void                    setIsRelay(const QVariant &isRelay);
        void                    setIsFavorite(const QVariant &isFavorite);

        QVariant                data(int role) const;
        bool                    setData(const QVariant &value, int role);
        bool                    isSmallerThan(const ParkingModel &other) const;

        QHash<int, QByteArray>  roleNames() const;

    private:
        int     m_id;
        QString m_name;
        QString m_status;
        QString m_lng;
        QString m_lat;
        int     m_free;
        int     m_total;
        bool    m_isRelay;
        bool    m_isFavorite;

    signals:
};

Q_DECLARE_METATYPE(ParkingModel)

#endif // PARKINGMODEL_H
