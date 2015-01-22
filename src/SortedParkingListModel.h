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

    private:
        ParkingListModel    *m_model;

    public slots:
        void                update();
        void                markAsFavorite(const int index, const bool isFav);
};

#endif // SORTEDPARKINGLISTMODEL_H
