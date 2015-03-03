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

#include "ParkingModel.h"

enum Roles {
    IdRole = Qt::UserRole + 1,          // Id of the parking lot
    NameRole,                           // Name of the parking lot
    StatusRole,                         // Status of the parking lot
    FreeRole,                           // Number of free places in the parking lot
    TotalRole,                          // Total number of places in the parking lot
    LongitudeRole,                      // Longitude
    LatitudeRole,                       // Latitude
    IsRelayRole,                        // True if the parking lot is a Parking+Tramway relay
    IsFavoriteRole                      // True if the parking has been marked as Favorite
};

ParkingModel::ParkingModel(QObject *parent) :
    QObject(parent),
    m_id(-1),
    m_name(""),
    m_status("status_3"),
    m_lng(""),
    m_lat(""),
    m_free(0),
    m_total(0),
    m_isRelay(false),
    m_isFavorite(false)
{
}

ParkingModel::ParkingModel(const ParkingModel &park, QObject *parent) :
    QObject(parent),
    m_id(park.m_id),
    m_name(park.m_name),
    m_status(park.m_status),
    m_lng(park.m_lng),
    m_lat(park.m_lat),
    m_free(park.m_free),
    m_total(park.m_total),
    m_isRelay(park.m_isRelay),
    m_isFavorite(park.m_isFavorite)
{
}

ParkingModel::ParkingModel(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_status("status_3"),
    m_lng(lng),
    m_lat(lat),
    m_free(0),
    m_total(0),
    m_isRelay(isRelay),
    m_isFavorite(isFavorite)
{
}

ParkingModel::~ParkingModel()
{
}

bool ParkingModel::operator<(const ParkingModel &other) const
{
    return this->isSmallerThan(other);
}

bool ParkingModel::isSmallerThan(ParkingModel const &other) const
{
    bool r = false;

    if(this->getIsFavorite() == other.getIsFavorite())
        r = this->getName() > other.getName();
    else
        r = this->getIsFavorite() < other.getIsFavorite();

    return r;
}

QHash<int, QByteArray> ParkingModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[StatusRole] = "status";
    roles[FreeRole] = "free";
    roles[TotalRole] = "total";
    roles[LongitudeRole] = "longitude";
    roles[LatitudeRole] = "latitude";
    roles[IsRelayRole] = "isRelay";
    roles[IsFavoriteRole] = "isFavorite";

    return roles;
}

int ParkingModel::getId() const
{
    return m_id;
}

QString ParkingModel::getName() const
{
    return m_name;
}

QString ParkingModel::getLongitude() const
{
    return m_lng;
}

QString ParkingModel::getLatitude() const
{
    return m_lat;
}

QString ParkingModel::getStatus() const
{
    return m_status;
}

int ParkingModel::getFree() const
{
    return m_free;
}

int ParkingModel::getTotal() const
{
    return m_total;
}

bool ParkingModel::getIsRelay() const
{
    return m_isRelay;
}

bool ParkingModel::getIsFavorite() const
{
    return m_isFavorite;
}


void ParkingModel::setId(const QVariant &id)
{
    this->m_id = id.toInt();
}

void ParkingModel::setName(const QVariant &name)
{
    this->m_name = name.toString();
}

void ParkingModel::setLongitude(const QVariant &lng)
{
    this->m_lng = lng.toString();
}

void ParkingModel::setLatitude(const QVariant &lat)
{
    this->m_lat = lat.toString();
}

void ParkingModel::setStatus(const QVariant &status)
{
    this->m_status = status.toString();
}

void ParkingModel::setFree(const QVariant &freep)
{
    this->m_free = freep.toInt();
}

void ParkingModel::setTotal(const QVariant &total)
{
    this->m_total = total.toInt();
}

void ParkingModel::setIsRelay(const QVariant &isRelay)
{
    this->m_isRelay = isRelay.toBool();
}

void ParkingModel::setIsFavorite(const QVariant &isFavorite)
{
    this->m_isFavorite = isFavorite.toBool();
}



QVariant ParkingModel::data(int role) const
{
    QVariant r = QVariant();

    switch(role)
    {
        case IdRole:
            r = this->getId();
            break;

        case Qt::DisplayRole:
        case NameRole:
            r = this->getName();
            break;

        case StatusRole:
            r = this->getStatus();
            break;

        case FreeRole:
            r = this->getFree();
            break;

        case TotalRole:
            r = this->getTotal();
            break;

        case LongitudeRole:
            r = this->getLongitude();
            break;

        case LatitudeRole:
            r = this->getLatitude();
            break;

        case IsRelayRole:
            r = this->getIsRelay();
            break;

        case IsFavoriteRole:
            r = this->getIsFavorite();
            break;
    }

    return r;
}

bool ParkingModel::setData(const QVariant &value, int role)
{
    bool r = true;

    switch(role)
    {
        case IdRole:
            this->setId(value);
            break;

        case Qt::DisplayRole:
        case NameRole:
            this->setName(value);
            break;

        case StatusRole:
            this->setStatus(value);
            break;

        case FreeRole:
            this->setFree(value);
            break;

        case TotalRole:
            this->setTotal(value);
            break;

        case LongitudeRole:
            this->setLongitude(value);
            break;

        case LatitudeRole:
            this->setLatitude(value);
            break;

        case IsRelayRole:
            this->setIsRelay(value);
            break;

        case IsFavoriteRole:
            this->setIsFavorite(value);
            break;

        default:
            r = false;
            break;
    }

    return r;
}
