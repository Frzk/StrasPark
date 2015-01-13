#ifndef PARKINGLISTMODEL_H
#define PARKINGLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>

#include "ParkingModel.h"

class ParkingListModel : public QAbstractListModel
{
    Q_OBJECT

    // Q_PROPERTY(...)

    public:
        // CONSTRUCTOR
        explicit ParkingListModel(QObject *parent = 0);

        // DESTRUCTOR
        ~ParkingListModel();

        // CONSTANTS
        static const QString source1;
        static const QString source2;

        // REIMPLEMENTED METHODS
        int                     rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant                data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QHash<int, QByteArray>  roleNames() const;
        Qt::ItemFlags           flags(const QModelIndex &index) const;
        QModelIndex             index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

        bool                    setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        bool                    appendRow(ParkingModel *model);
        bool                    appendRows(QList<ParkingModel *> &items);
        bool                    insertRow(int row, ParkingModel *model);
        bool                    insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool                    removeRow(int row, const QModelIndex &parent = QModelIndex());
        bool                    removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
        void                    clear();

        bool                    hasIndex(int row, int column, const QModelIndex &parent) const;
        ParkingModel*           itemAt(const QModelIndex &index) const;

    signals:
        void countChanged(int);
        void refreshNeeded();
        void listUpToDate();

    private:
        ParkingModel            *m_prototype;
        QList<ParkingModel*>    m_parkings;

    private slots:
        void refresh();
        void fillList();
};

#endif // PARKINGLISTMODEL_H
