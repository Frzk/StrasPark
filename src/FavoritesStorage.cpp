#include "FavoritesStorage.h"

FavoritesStorage::FavoritesStorage(QObject *parent) :
    QObject(parent)
{   
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if(!path.isEmpty())
    {
        QDir dir = QDir(path);

        if(!dir.exists())
            dir.mkpath(path);

        path.append(QDir::separator()).append("favorites");

        this->m_file = new QFile(QDir::toNativeSeparators(path));
    }
}

FavoritesStorage::~FavoritesStorage()
{
    delete this->m_file;
}

bool FavoritesStorage::load()
{
    bool r = false;

    if(this->m_file->open(QIODevice::ReadOnly))
    {
        QDataStream in(this->m_file);
        in >> this->m_favorites;
        this->m_file->close();

        r = true;
    }

    qDebug() << this->m_favorites;

    return r;
}

QSet<int> FavoritesStorage::get() const
{
    return this->m_favorites;
}

bool FavoritesStorage::save() const
{
    bool r = false;

    if(this->m_file->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QDataStream out(this->m_file);
        out << this->m_favorites;
        this->m_file->close();

        r = true;
    }

    return r;
}

bool FavoritesStorage::add(const int id)
{
    this->m_favorites.insert(id);
    return this->save();
}

bool FavoritesStorage::remove(const int id)
{
    this->m_favorites.remove(id);
    return this->save();
}

bool FavoritesStorage::contains(const int id) const
{
    return this->m_favorites.contains(id);
}
