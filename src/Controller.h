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

    Q_PROPERTY(bool isRefreshing READ isRefreshing NOTIFY isRefreshingChanged)
    Q_PROPERTY(QString lastUpdate READ lastUpdate NOTIFY lastUpdateChanged)

    public:
        explicit Controller(QObject *parent = 0);

        ~Controller();

        SortedParkingListModel*             model() const;
        static QHash<int, QJsonObject>      jsonArrayToHashMap(const QJsonArray &a);
        bool                                isRefreshing() const;
        QString                             lastUpdate() const;

        Q_INVOKABLE void                    triggerUpdate();

    private:
        SortedParkingListModel      *m_model;
        FavoritesStorage            *m_fav;
        JSONRequest                 *m_req1;
        JSONRequest                 *m_req2;
        bool                        m_isRefreshing;
        QString                     m_refreshDate;

    signals:
        void    modelFilled();
        void    isRefreshingChanged();
        void    lastUpdateChanged();

    private slots:
        void    fillModel(const QJsonDocument &d);
        void    refresh(const QJsonDocument &d);
        void    updateData();
        void    handleNetworkError(const QNetworkReply::NetworkError &errcode);
        bool    updateFavorite(int id, bool value);
};

#endif // CONTROLLER_H
