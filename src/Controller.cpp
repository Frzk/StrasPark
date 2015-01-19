#include "Controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    this->m_model = new SortedParkingListModel(this);

    // TEST PURPOSES * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    /*
    ParkingModel *item1 = new ParkingModel(1, "Parking test 1", "7.12345", "48.12345", false, true);
    ParkingModel *item2 = new ParkingModel(2, "Parking test 2", "7.12345", "48.12345", false, true);
    ParkingModel *item3 = new ParkingModel(3, "Parking test 3", "7.12345", "48.12345", false, false);

    this->m_model->model()->appendRow(item2);
    this->m_model->model()->appendRow(item3);
    this->m_model->model()->appendRow(item1);
    */

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    this->m_fav = new FavoritesStorage(this);
    this->m_fav->load();

    this->m_req1 = new JSONRequest(this);
    this->m_req2 = new JSONRequest(this);

    QObject::connect(this->m_model->model(), SIGNAL(isFavoriteChanged(int, bool)), this, SLOT(updateFavorite(int, bool)));
    QObject::connect(this, SIGNAL(modelFilled()), this, SLOT(updateData()));

    QObject::connect(this->m_req1, SIGNAL(documentReady(const QJsonDocument)), this, SLOT(fillModel(const QJsonDocument)));
    QObject::connect(this->m_req2, SIGNAL(documentReady(const QJsonDocument)), this, SLOT(refresh(const QJsonDocument)));

    this->m_req1->request(ParkingListModel::source1);
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

void Controller::updateData()
{
    // Set Favorites.
    if(this->m_fav != NULL)
    {
        for(int i=0 ; i<this->m_model->model()->rowCount() ; i++)
        {
            QModelIndex idx = this->m_model->model()->index(i, 0);
            int id = this->m_model->model()->data(idx, Qt::UserRole + 1).toInt();

            if(this->m_fav->contains(id))
            //    qDebug() << "is Favorite !";
                this->m_model->model()->setData(idx, QVariant(true), Qt::UserRole + 9);
        }
    }

    // Launch timer.
    this->m_req2->request(ParkingListModel::source2);
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
    qDebug() << d;
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
