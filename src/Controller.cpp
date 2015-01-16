#include "Controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    this->m_model = new SortedParkingListModel(this);

    // TEST PURPOSES * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    ParkingModel *item1 = new ParkingModel(1, "Parking test 1", "7.12345", "48.12345", false, true);
    ParkingModel *item2 = new ParkingModel(2, "Parking test 2", "7.12345", "48.12345", false, true);
    ParkingModel *item3 = new ParkingModel(3, "Parking test 3", "7.12345", "48.12345", false, false);

    this->m_model->model()->appendRow(item2);
    this->m_model->model()->appendRow(item3);
    this->m_model->model()->appendRow(item1);

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    /*
    this->m_fav = new FavoritesStorage(this);
    this->m_fav->load();
    */
    this->m_req1 = new JSONRequest(this);
    this->m_req2 = new JSONRequest(this);

    QObject::connect(this->m_req1, SIGNAL(documentReady(const QJsonDocument)), this->m_model->model(), SLOT(fillModel(const QJsonDocument)));
    QObject::connect(this->m_req2, SIGNAL(documentReady(const QJsonDocument)), this->m_model->model(), SLOT(refresh(const QJsonDocument)));

    QObject::connect(this->m_model->model(), SIGNAL(modelFilled()), this, SLOT(updateData()));

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


    // Launch timer.
    this->m_req2->request(ParkingListModel::source2);
}
