#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "ParkingModel.h"
#include "ParkingListModel.h"
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
        void    modelFilled();

    private slots:
        void    fillModel(const QJsonDocument &d);
        void    refresh(const QJsonDocument &d);
        void    updateData();
        bool    updateFavorite(int id, bool value);
};

#endif // CONTROLLER_H
