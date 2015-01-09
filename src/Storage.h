#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QString>
#include <QVariant>

#include "ParkingListModel.h"

class Storage : public QObject
{
    Q_OBJECT

    public:
        explicit Storage(QObject *parent = 0);
        ~Storage();

        bool openDB();
        bool deleteDB();
        QSqlError lastError();

    private:
        QString m_path;
        QSqlDatabase m_db;

        bool createTables();
        bool insertParking(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite);
        bool getAllParkings(ParkingListModel *model);
        bool markAsFavorite(int id, bool isFavorite);
        int countParking();
};

#endif // STORAGE_H
