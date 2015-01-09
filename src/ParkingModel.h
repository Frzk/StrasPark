#ifndef PARKINGMODEL_H
#define PARKINGMODEL_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QVariant>

class ParkingModel : public QObject
{
    Q_OBJECT

    public:
        explicit ParkingModel(QObject *parent = 0);
        explicit ParkingModel(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite, QObject *parent = 0);

        ~ParkingModel();

        int                     getId() const;
        QString                 getName() const;
        QString                 getStatus() const;
        QString                 getLongitude() const;
        QString                 getLatitude() const;
        int                     getFree() const;
        int                     getTotal() const;
        bool                    getIsRelay() const;
        bool                    getIsFavorite() const;

        QVariant                data(int role) const;
        bool                    setData(const QVariant &value, int role);

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
        void dataChanged();
};

#endif // PARKINGMODEL_H
