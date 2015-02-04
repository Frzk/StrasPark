#include "Controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    this->m_model = new SortedParkingListModel(this);
    this->m_fav = new FavoritesStorage(this);
    this->m_req1 = new JSONRequest(this);
    this->m_req2 = new JSONRequest(this);
    this->m_isRefreshing = false;
    this->m_coverFavoriteIndex = -1;

    this->m_fav->load();

    QObject::connect(this->m_model->model(), SIGNAL(isFavoriteChanged(int, bool)), this, SLOT(updateFavorite(int, bool)));
    QObject::connect(this, SIGNAL(modelFilled()), this, SLOT(updateData()));

    QObject::connect(this->m_req1, SIGNAL(documentReady(const QJsonDocument)), this, SLOT(fillModel(const QJsonDocument)));
    QObject::connect(this->m_req1, SIGNAL(networkError(const QNetworkReply::NetworkError&)), this, SLOT(handleNetworkError(const QNetworkReply::NetworkError&)));

    QObject::connect(this->m_req2, SIGNAL(documentReady(const QJsonDocument)), this, SLOT(refresh(const QJsonDocument)));
    QObject::connect(this->m_req2, SIGNAL(networkError(const QNetworkReply::NetworkError&)), this, SLOT(handleNetworkError(const QNetworkReply::NetworkError&)));

    this->triggerUpdate();
}

Controller::~Controller()
{
    delete this->m_model;
    delete this->m_fav;
    delete this->m_req1;
    delete this->m_req2;
}

SortedParkingListModel* Controller::model() const
{
    return this->m_model;
}

QString Controller::lastUpdate() const
{
    return this->m_refreshDate;
}

bool Controller::isRefreshing() const
{
    return this->m_isRefreshing;
}

bool Controller::canRefresh() const
{
    QDateTime now = QDateTime::currentDateTimeUtc();
    return (!this->m_lastSuccessfulRefresh.isValid() || this->m_lastSuccessfulRefresh.secsTo(now) > Controller::refreshInterval);
}

// PUBLIC SLOTS
void Controller::triggerUpdate()
{
    this->updateData();
}

QVariantMap Controller::nextFavorite()
{
    QVariantMap r;

    if(this->m_fav->get().count() > 0)
    {
        int nextIndex = this->m_coverFavoriteIndex + 1;

        if(!this->m_model->get(nextIndex).value("isFavorite").toBool())
            nextIndex = 0;

        r = this->m_model->get(nextIndex);
        this->m_coverFavoriteIndex = nextIndex;
    }

    return r;
}


void Controller::updateData()
{
    if(this->model()->rowCount() > 0)
    {
        if(this->canRefresh())
        {
            this->m_req2->request(ParkingListModel::source2);
            this->m_isRefreshing = true;
            emit isRefreshingChanged();
        }
    }
    else
    {
        this->m_req1->request(ParkingListModel::source1);
        this->m_isRefreshing = true;
        emit isRefreshingChanged();
    }
}

void Controller::fillModel(const QJsonDocument &d)
{
    QJsonObject obj = d.object();
    QJsonValue v = obj.value("s");

    if(v != QJsonValue::Undefined)
    {
        QJsonArray parks = v.toArray();
        QList<ParkingModel *> l;

        foreach(const QJsonValue p, parks)
        {
            QJsonObject o = p.toObject();
            //FIXME: sounds like a good candidate for a memory leak...
            ParkingModel *parkingLot = new ParkingModel(
                        o.value("id").toString().toInt(),
                        o.value("ln").toString(),
                        o.value("go").toObject().value("x").toString(),
                        o.value("go").toObject().value("y").toString(),
                        (o.value("price_fr").toString() == "Parking relais CTS"),
                        (this->m_fav->contains(o.value("id").toString().toInt()))
            );

            l << parkingLot;
        }

        this->m_model->model()->appendRows(l);
    }
    //else
    //FIXME

    emit modelFilled();
}

void Controller::refresh(const QJsonDocument &d)
{
    QJsonObject obj = d.object();
    //FIXME: make this a QDateTime with i18n :
    //       also change the Q_PROPERTY accordingly.
    this->m_refreshDate = obj.value("datatime").toString();
    emit lastUpdateChanged();

    QJsonValue v = obj.value("s");

    if(v != QJsonValue::Undefined)
    {
        // Update lastSuccessfulRefresh to the current date + time so we can prevent abusive refresh.
        this->m_lastSuccessfulRefresh = QDateTime::currentDateTimeUtc();

        // Transform JSON to QHash for a quicker access.
        QHash<int, QJsonObject> values = Controller::jsonArrayToHashMap(v.toArray());

        // Actually update the data.
        for(int i=0 ; i<this->m_model->model()->rowCount() ; i++)
        {
            QModelIndex idx = this->m_model->model()->index(i, 0);
            int id = this->m_model->model()->data(idx, Qt::UserRole + 1).toInt();

            QJsonObject o = values.take(id);
            QString newStatus = o.value("ds").toString();
            int freePlaces = o.value("df").toString().toInt();
            int totalPlaces = o.value("dt").toString().toInt();

            this->m_model->model()->setData(idx, QVariant(newStatus), Qt::UserRole + 3);    // StatusRole
            this->m_model->model()->setData(idx, QVariant(freePlaces), Qt::UserRole + 4);   // FreeRole
            this->m_model->model()->setData(idx, QVariant(totalPlaces), Qt::UserRole + 5);  // TotalRole
        }
    }
    //else
    //FIXME

    this->m_isRefreshing = false;
    emit isRefreshingChanged();
}

bool Controller::updateFavorite(int id, bool value)
{
    bool r = false;

    if(value)
        r = this->m_fav->add(id);
    else
        r = this->m_fav->remove(id);

    return r;
}

void Controller::handleNetworkError(const QNetworkReply::NetworkError &errcode)
{
    qDebug() << errcode;
    this->m_isRefreshing = false;
    emit isRefreshingChanged();
}



QHash<int, QJsonObject> Controller::jsonArrayToHashMap(const QJsonArray &a)
{
    QHash<int, QJsonObject> r;

    for(int i=0 ; i<a.size() ; i++)
    {
        QJsonObject obj = a.at(i).toObject();
        int id = obj.value("id").toString().toInt();
        r.insert(id, obj);
    }

    return r;
}
