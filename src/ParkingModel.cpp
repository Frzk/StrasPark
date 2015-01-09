#include "ParkingModel.h"

enum {
    IdRole = Qt::UserRole + 1,          // Id of the parking lot
    NameRole = Qt::UserRole + 2,        // Name of the parking lot
    StatusRole = Qt::UserRole + 3,      // Status of the parking lot
    FreeRole = Qt::UserRole + 4,        // Number of free places in the parking lot
    TotalRole = Qt::UserRole + 5,       // Total number of places in the parking lot
    LongitudeRole = Qt::UserRole + 6,   // Longitude
    LatitudeRole = Qt::UserRole + 7,    // Latitude
    IsRelayRole = Qt::UserRole + 8,     // True if the parking lot is a Parking+Tramway relay
    IsFavoriteRole = Qt::UserRole + 9   // True if the parking has been marked as Favorite
};

ParkingModel::ParkingModel(QObject *parent) :
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

ParkingModel::ParkingModel(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite, QObject *parent) :
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
    //FIXME

    emit dataChanged();

    return true;
}
