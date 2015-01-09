#include "Storage.h"

Storage::Storage(QObject *parent) :
    QObject(parent)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if(!path.isEmpty())
    {
        QDir dir = QDir(path);

        if(!dir.exists())
            dir.mkpath(path);

        path.append(QDir::separator()).append("db.sqlite");
        m_path = QDir::toNativeSeparators(path);
    }
}

Storage::~Storage()
{
    m_db.close();
}


/**
 * @brief Opens the database
 *
 * @return bool
 */
bool Storage::openDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_path);

    return m_db.open();
}

/**
 * @brief Deletes the database
 *
 * @return bool
 */
bool Storage::deleteDB()
{
    // Makes sure the database is closed :
    m_db.close();

    return QFile::remove(m_path);
}

/**
 * @brief Returns the last error
 *
 * @return QSqlError
 */
QSqlError Storage::lastError()
{
    return m_db.lastError();
}

/**
 * @brief Create the needed tables for the database.
 *
 * @return bool
 */
bool Storage::createTables()
{
    bool r = false;

    if(m_db.isOpen())
    {
        QSqlQuery query;

        query.prepare("CREATE TABLE IF NOT EXISTS parkinglots ("
                    "id INTEGER PRIMARY KEY,"
                    " name TEXT,"
                    " lng TEXT,"
                    " lat TEXT,"
                    " isRelay BOOLEAN,"
                    " isFavorite BOOLEAN)");

        r = query.exec();
    }

    return r;
}

/**
 * @brief Inserts a new parking lot in the database.
 *
 * @param id            id of the parking lot, as given by the JSON source.
 * @param name          name of the parking lot.
 * @param lng           longitude coordinate of the parking lot.
 * @param lat           latitude coordinate of the parking lot.
 * @param isRelay       true if this parking lot is a tramway relay.
 * @param isFavorite    true if this parking lot has been marked as favorite.
 *
 * @return bool
 */
bool Storage::insertParking(int id, QString name, QString lng, QString lat, bool isRelay, bool isFavorite)
{
    bool r = false;

    if(m_db.isOpen())
    {
        QSqlQuery query;

        query.prepare("INSERT INTO parkinglots (id, name, lng, lat, isRelay, isFavorite) "
                    "VALUES(:id, :name, :lng, :lat, :isRelay, :isFavorite)");

        query.bindValue(":id", id, QSql::In);
        query.bindValue(":name", name, QSql::In);
        query.bindValue(":lng", lng, QSql::In);
        query.bindValue(":lat", lat, QSql::In);
        query.bindValue(":isRelay", isRelay, QSql::In);
        query.bindValue(":isFavorite", isFavorite, QSql::In);

        r = query.exec();
    }

    return r;
}

/**
 * @brief Set the parking lot isFavorite to the given value.
 *
 * @param id            id of the parking lot, as given by the JSON source.
 * @param isFavorite    true if this parking lot must be marked as favorite, false otherwise.
 *
 * @return bool
 */
bool Storage::markAsFavorite(int id, bool isFavorite)
{
    bool r = false;

    if(m_db.isOpen())
    {
        QSqlQuery query;

        query.prepare("UPDATE parkinglots SET (isFavorite=:isFavorite) WHERE id=:id");

        query.bindValue(":id", id, QSql::In);
        query.bindValue(":isFavorite", isFavorite, QSql::In);

        r = query.exec();
    }

    return r;
}

/**
 * @brief Storage::countParking
 *
 * @return
 */
int Storage::countParking()
{
    int r = -1;

    if(m_db.isOpen())
    {
        QSqlQuery query;

        query.prepare("SELECT COUNT(id) AS nb FROM parkinglots");

        if(query.first())
        {
            r = query.value(0).toInt();
        }
    }

    return r;
}

bool Storage::getAllParkings(ParkingListModel *model)
{
    bool r = false;
    QList<ParkingModel*> l = QList<ParkingModel*>();

    QSqlQuery query;

    query.prepare("SELECT id, name, lng, lat, isRelay, isFavorite FROM parkingslots ORDER BY isFavorite DESC, name ASC");

    r = query.exec();

    while(query.next())
    {
        ParkingModel *p = new ParkingModel(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toBool(),
            query.value(5).toBool()
        );

        l.append(p);
    }

    model->clear();
    model->appendRows(l);

    return r;
}
