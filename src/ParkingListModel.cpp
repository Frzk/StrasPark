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

#include "ParkingListModel.h"

ParkingListModel::ParkingListModel(QObject *parent) : QAbstractListModel(parent), m_dataSource(0)
{
    this->m_prototype = new ParkingModel();
    this->m_parkings = QList<ParkingModel *>();
    this->m_fav = new FavoritesStorage(this);
    this->m_isRefreshing = false;
    // this->m_dataSource is set in QML.

    //FIXME: is this the right place ?
    this->m_fav->load();

    QObject::connect(this, &ParkingListModel::modelFilled, this, &ParkingListModel::updateData);
    QObject::connect(this, &ParkingListModel::isFavoriteChanged, this, &ParkingListModel::updateFavorite);
}

ParkingListModel::~ParkingListModel()
{
    delete this->m_prototype;
    this->m_prototype = NULL;

    delete this->m_fav;
    delete this->m_dataSource;

    this->clear();
    this->m_parkings.clear();
}

QHash<int, QByteArray> ParkingListModel::roleNames() const
{
    return this->m_prototype->roleNames();
}

int ParkingListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->m_parkings.size();
}

QVariant ParkingListModel::data(const QModelIndex &index, int role) const
{
    QVariant r = QVariant();

    if(index.isValid() && index.row() >=0 && index.row() < this->m_parkings.size())
        r = this->m_parkings.at(index.row())->data(role);

    return r;
}

Qt::ItemFlags ParkingListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags r = Qt::ItemIsEnabled;

    if(index.isValid())
        r = QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    return r;
}

QModelIndex ParkingListModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex r;

    if(this->hasIndex(row, column, parent))
        r = this->createIndex(row, column, this->m_parkings.at(row));

    return r;
}

bool ParkingListModel::hasIndex(int row, int column, const QModelIndex &parent) const
{
    bool r = false;
    if(row >= 0 && row < this->rowCount(parent) && column == 0)
        r = true;

    return r;
}

bool ParkingListModel::appendRow(ParkingModel *item)
{
    bool r = false;

    if(item != NULL)
    {
        this->appendRows(QList<ParkingModel *>() << item);

        emit countChanged(this->rowCount());

        r = true;
    }

    return r;
}

bool ParkingListModel::appendRows(QList<ParkingModel *> &items)
{
    bool r = false;

    if(items.size() > 0)
    {
        this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount() + items.size() - 1);

        foreach(ParkingModel *item, items)
        {
            this->m_parkings.append(item);
        }

        this->endInsertRows();

        emit countChanged(this->rowCount());

        r = true;
    }

    return r;
}

bool ParkingListModel::insertRow(int row, ParkingModel *item)
{
    bool r = false;

    if(item != NULL)
    {
        this->beginInsertRows(QModelIndex(), row, row);
        this->m_parkings.insert(row, item);
        this->endInsertRows();

        emit countChanged(this->rowCount());

        r = true;
    }

    return r;
}

bool ParkingListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    this->beginInsertRows(parent, row, row + count - 1);

    for(int i=row ; i<(row + count -1) ; i++)
    {
        //FIXME: is this ok ?
        this->m_parkings.insert(i, new ParkingModel(this));
    }

    this->endInsertRows();

    return true;
}

bool ParkingListModel::removeRow(int row, const QModelIndex &parent)
{
    bool r = false;

    if(row >= 0 && row < this->rowCount())
    {
        this->beginRemoveRows(parent, row, row);

        delete this->m_parkings.at(row);
        this->m_parkings.removeAt(row);

        this->endRemoveRows();

        emit countChanged(this->rowCount());

        r = true;
    }

    return r;
}

bool ParkingListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool r = false;

    if(row >= 0 && count > 0 && (row + count) <= this->rowCount())
    {
        this->beginRemoveRows(parent, row, row + count - 1);

        for(int i=(row + count - 1) ; i <= row ; i--)
        {
            delete this->m_parkings.at(i);
            this->m_parkings.removeAt(i);
        }

        this->endRemoveRows();

        emit countChanged(this->rowCount());

        r = true;
    }

    return r;
}

void ParkingListModel::clear()
{
    if(this->rowCount() > 0)
    {
        this->removeRows(0, this->rowCount());

        emit(countChanged(this->rowCount()));
    }
}

bool ParkingListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool r = false;
    ParkingModel *p = this->itemAt(index);

    if(p != NULL)
    {
        r = p->setData(value, role);

        if(r)
        {
            if(role == Qt::UserRole + 9)
            {
                int id = p->data(Qt::UserRole + 1).toInt();
                emit isFavoriteChanged(id, value.toBool());
            }

            emit dataChanged(index, index);
        }
        //FIXME: should we emit something else here ? (error ?)
    }

    return r;
}

ParkingModel* ParkingListModel::itemAt(const QModelIndex &index) const
{
    ParkingModel* r = NULL;

    if(index.isValid() && index.row() < this->rowCount())
    {
        r = this->m_parkings.at(index.row());
    }

    return r;
}



// Q_PROPERTY RELATED

DataSource* ParkingListModel::dataSource() const
{
    return this->m_dataSource;
}

bool ParkingListModel::isRefreshing() const
{
    return this->m_isRefreshing;
}

QDateTime ParkingListModel::lastUpdate() const
{
    return this->m_lastSuccessfulRefresh;
}

void ParkingListModel::setDataSource(DataSource *src)
{
    if(this->m_dataSource != src)
    {
        if(this->m_dataSource)
        {
            // We first have to disconnect the old controller :
            QObject::disconnect(this->m_dataSource, SIGNAL(listReady()), 0, 0);
            QObject::disconnect(this->m_dataSource, SIGNAL(dataReady()), 0, 0);
            QObject::disconnect(this->m_dataSource, SIGNAL(networkError()), 0 ,0);
        }

        this->m_dataSource = src;

        if(this->m_dataSource)
        {
            // And now we can "plug" the new one :
            QObject::connect(this->m_dataSource, &DataSource::listReady, this, &ParkingListModel::fillModel);
            QObject::connect(this->m_dataSource, &DataSource::dataReady, this, &ParkingListModel::refresh);
            QObject::connect(this->m_dataSource, &DataSource::networkError, this, &ParkingListModel::handleNetworkError);
        }

        emit dataSourceChanged();
    }
}



// SLOTS

void ParkingListModel::triggerUpdate()
{
    this->updateData();
}

// Called when modelFilled signal is emitted
// Or manually via triggerUpdate()
void ParkingListModel::updateData()
{
    if(this->rowCount() > 0)
    {
        if(this->canRefresh())
        {
            this->m_dataSource->getData();
            this->m_isRefreshing = true;
            emit isRefreshingChanged();
        }
    }
    else
    {
        this->m_dataSource->getList();
        this->m_isRefreshing = true;
        emit isRefreshingChanged();
    }
}

// Called when m_dataSource emits the listReady signal.
void ParkingListModel::fillModel(const QJsonDocument &d)
{
    QJsonObject obj = d.object();
    QJsonValue v = obj.value("s");

    if(v != QJsonValue::Undefined)
    {
        QJsonArray parks = v.toArray();
        QList<ParkingModel *> l;

        foreach(const QJsonValue p, parks)
        {
            QJsonObject o = p.toObject();
            //FIXME: sounds like a good candidate for a memory leak...
            ParkingModel *parkingLot = new ParkingModel(
                        o.value("id").toString().toInt(),
                        o.value("ln").toString(),
                        o.value("go").toObject().value("x").toString(),
                        o.value("go").toObject().value("y").toString(),
                        (o.value("price_fr").toString() == "Parking relais CTS"),
                        (this->m_fav->contains(o.value("id").toString().toInt()))
            );

            l << parkingLot;
        }

        this->appendRows(l);
    }
    //else
    //FIXME

    emit modelFilled();
}

// Called when m_dataSource emits the dataReady signal.
void ParkingListModel::refresh(const QJsonDocument &d)
{
    QJsonObject obj = d.object();
    QJsonValue v = obj.value("s");

    if(v != QJsonValue::Undefined)
    {
        // Update lastSuccessfulRefresh to the current date + time so we can prevent abusive refresh.
        this->m_lastSuccessfulRefresh = QDateTime::currentDateTimeUtc();
        emit lastUpdateChanged();

        // Transform JSON to QHash for a quicker access.
        QHash<int, QJsonObject> values = ParkingListModel::jsonArrayToHashMap(v.toArray());

        // Actually update the data.
        for(int i=0 ; i<this->rowCount() ; i++)
        {
            QModelIndex idx = this->index(i, 0);
            int id = this->data(idx, Qt::UserRole + 1).toInt();

            QJsonObject o = values.take(id);
            QString newStatus = o.value("ds").toString();
            int freePlaces = o.value("df").toString().toInt();
            int totalPlaces = o.value("dt").toString().toInt();

            this->setData(idx, QVariant(newStatus), Qt::UserRole + 3);    // StatusRole
            this->setData(idx, QVariant(freePlaces), Qt::UserRole + 4);   // FreeRole
            this->setData(idx, QVariant(totalPlaces), Qt::UserRole + 5);  // TotalRole
        }

        emit dataRefreshed();
    }
    //else
    //FIXME

    this->m_isRefreshing = false;
    emit isRefreshingChanged();
}

// Called when m_dataSource emits the networkError signal.
void ParkingListModel::handleNetworkError(const QNetworkReply::NetworkError &errcode)
{
    qDebug() << errcode;
    this->m_isRefreshing = false;
    emit isRefreshingChanged();
}

// Called when favoriteChanged is emitted.
bool ParkingListModel::updateFavorite(int id, bool value)
{
    bool r = false;

    if(value)
        r = this->m_fav->add(id);
    else
        r = this->m_fav->remove(id);

    return r;
}



// OTHER METHODS

bool ParkingListModel::canRefresh() const
{
    QDateTime now = QDateTime::currentDateTimeUtc();
    return (!this->m_lastSuccessfulRefresh.isValid() || this->m_lastSuccessfulRefresh.secsTo(now) > ParkingListModel::refreshInterval);
}

QHash<int, QJsonObject> ParkingListModel::jsonArrayToHashMap(const QJsonArray &a)
{
    QHash<int, QJsonObject> r;

    for(int i=0 ; i<a.size() ; i++)
    {
        QJsonObject obj = a.at(i).toObject();
        int id = obj.value("id").toString().toInt();
        r.insert(id, obj);
    }

    return r;
}
