#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "SortedParkingListModel.h"
#include "FavoritesStorage.h"
#include "JSONRequest.h"

class Controller : public QObject
{
    Q_OBJECT

    public:
        explicit Controller(QObject *parent = 0);

        ~Controller();

        SortedParkingListModel*     model() const;

    private:
        SortedParkingListModel      *m_model;
        FavoritesStorage            *m_fav;
        JSONRequest                 *m_req1;
        JSONRequest                 *m_req2;

    signals:

    private slots:
        void    updateData();
};

#endif // CONTROLLER_H
