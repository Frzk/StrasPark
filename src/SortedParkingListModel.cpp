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

#include "SortedParkingListModel.h"

SortedParkingListModel::SortedParkingListModel() :
    QSortFilterProxyModel()
{
    this->m_model = new ParkingListModel(this);

    this->setSourceModel(this->m_model);
    this->sort(0, Qt::DescendingOrder);
    this->setDynamicSortFilter(true);

    QObject::connect(this->m_model, &ParkingListModel::dataSourceChanged, this, &SortedParkingListModel::emitDataSourceChanged);
    QObject::connect(this->m_model, &ParkingListModel::isRefreshingChanged, this, &SortedParkingListModel::emitIsRefreshingChanged);
    QObject::connect(this->m_model, &ParkingListModel::lastUpdateChanged, this, &SortedParkingListModel::emitLastUpdateChanged);
}

SortedParkingListModel::~SortedParkingListModel()
{
    delete this->m_model;
}



// REIMPLEMENTED

bool SortedParkingListModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    //FIXME: don't know which method is the best :
/*
    ParkingListModel *model = qobject_cast<ParkingListModel *>(this->sourceModel());
    ParkingModel *l = model->itemAt(left);
    ParkingModel *r = model->itemAt(right);

    return *l < *r;
*/
    bool r;

    bool leftIsFavorite = this->sourceModel()->data(left, Qt::UserRole + 9).toBool();
    bool rightIsFavorite = this->sourceModel()->data(right, Qt::UserRole + 9).toBool();

    QString leftName = this->sourceModel()->data(left, Qt::UserRole + 2).toString();
    QString rightName = this->sourceModel()->data(right, Qt::UserRole + 2).toString();

    if(leftIsFavorite == rightIsFavorite)
        r = (leftName > rightName);
    else
        r = (leftIsFavorite < rightIsFavorite);

    return r;
}



// Q_PROPERTY RELATED

DataSource* SortedParkingListModel::dataSource() const
{
    return this->m_model->dataSource();
}

bool SortedParkingListModel::isRefreshing() const
{
    return this->m_model->isRefreshing();
}

QDateTime SortedParkingListModel::lastUpdate() const
{
    return this->m_model->lastUpdate();
}

void SortedParkingListModel::setDataSource(DataSource* src)
{
    this->m_model->setDataSource(src);
}



// SLOTS

void SortedParkingListModel::emitDataSourceChanged()
{
    emit dataSourceChanged();
}

void SortedParkingListModel::emitIsRefreshingChanged()
{
    emit isRefreshingChanged();
}

void SortedParkingListModel::emitLastUpdateChanged()
{
    emit lastUpdateChanged();
}



// OTHER METHODS

void SortedParkingListModel::triggerUpdate() const
{
    this->m_model->triggerUpdate();
}

QVariantMap SortedParkingListModel::getParking(const int row) const
{
    QVariantMap r;
    QModelIndex idx = this->index(row, 0);
    QHashIterator<int, QByteArray> i(this->roleNames());

    while(i.hasNext())
    {
        i.next();
        r.insert(i.value(), this->data(idx, i.key()));
    }

    return r;
}


/*
bool Controller::updateFavorite(int id, bool value)
{
    bool r = false;

    if(value)
        r = this->m_fav->add(id);
    else
        r = this->m_fav->remove(id);

    return r;
}
*/
