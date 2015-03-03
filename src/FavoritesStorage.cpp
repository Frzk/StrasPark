/*
  Copyright (C) 2015 François KUBLER
  Contact: François Kubler <francois@kubler.org>
  All rights reserved.

    This file is part of StrasbourgParking.

    StrasbourgParking is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    StrasbourgParking is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
