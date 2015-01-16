#include "ParkingListModel.h"

const QString ParkingListModel::source1 = QString("http://carto.strasmap.eu/remote.amf.json/Parking.geometry");
const QString ParkingListModel::source2 = QString("http://carto.strasmap.eu/remote.amf.json/Parking.status");


ParkingListModel::ParkingListModel(QObject *parent) : QAbstractListModel(parent)
{
    //FIXME:
    this->m_prototype = new ParkingModel();
    this->m_parkings = QList<ParkingModel *>();
    this->m_db = new FavoritesStorage();

    //QObject::connect(this, SIGNAL(refreshNeeded()), this, SLOT(refresh()));
    //QObject::connect(this, SIGNAL(listUpToDate()), this, SLOT(fillList()));
}

ParkingListModel::~ParkingListModel()
{
    delete this->m_prototype;
    this->m_prototype = NULL;
    this->clear();

    delete this->m_db;
}

QHash<int,QByteArray> ParkingListModel::roleNames() const
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
    if(row >= 0 && row < rowCount(parent) && column == 0)
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

void ParkingListModel::refresh()
{

}

void ParkingListModel::fillList(const QJsonDocument &d)
{
    qDebug() << d;
}
