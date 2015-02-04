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

void SortedParkingListModel::update()
{
    qDebug() << "Triggered from QML.";
}

void SortedParkingListModel::markAsFavorite(const int index, const bool isFav)
{
    QModelIndex idx = this->mapToSource(this->index(index, 0));
    this->sourceModel()->setData(idx, isFav, Qt::UserRole + 9);
}

QVariantMap SortedParkingListModel::get(const int row) const
{
    QVariantMap r;

    QModelIndex idx = this->index(row, 0);
    QHash<int, QByteArray> roles = this->model()->roleNames();

    QHash<int, QByteArray>::const_iterator i = roles.constBegin();

    while(i != roles.constEnd())
    {
        r[i.value()] = this->data(idx, i.key());
        i++;
    }

    return r;
}
