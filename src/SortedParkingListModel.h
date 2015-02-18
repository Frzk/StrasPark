#ifndef SORTEDPARKINGLISTMODEL_H
#define SORTEDPARKINGLISTMODEL_H

#include <QSortFilterProxyModel>
#include <QVariant>

#include "ParkingListModel.h"
#include "ParkingModel.h"

class SortedParkingListModel : public QSortFilterProxyModel
{
    Q_OBJECT

    public:
        // CONSTRUCTOR :
        explicit SortedParkingListModel(QObject *parent = 0);

        // DESTRUCTOR :
        ~SortedParkingListModel();

        // REIMPLEMENTED :
        bool                lessThan(const QModelIndex &left, const QModelIndex &right) const;

        // METHODS :
        ParkingListModel*   model() const;

        // Q_INVOKABLE :
        Q_INVOKABLE QVariantMap     getParking(const int row) const;

    private:
        ParkingListModel    *m_model;

    signals:
        void                favoriteChanged(int row, bool isFav);

    public slots:
        void                markAsFavorite(const int row, const bool isFav);
};

#endif // SORTEDPARKINGLISTMODEL_H
