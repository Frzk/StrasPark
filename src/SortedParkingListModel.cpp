#include "SortedParkingListModel.h"

SortedParkingListModel::SortedParkingListModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    this->m_model = new ParkingListModel(this);

    this->setSourceModel(this->m_model);
    this->sort(0, Qt::DescendingOrder);
    this->setDynamicSortFilter(true);
}

SortedParkingListModel::~SortedParkingListModel()
{
    delete this->m_model;
}

ParkingListModel* SortedParkingListModel::model() const
{
    return this->m_model;
}

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
