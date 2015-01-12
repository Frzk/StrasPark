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

#endif // PARKINGMODEL_H
