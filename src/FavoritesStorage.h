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

#ifndef FAVORITESSTORAGE_H
#define FAVORITESSTORAGE_H

#include <QObject>

#include <QDebug>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QSet>
#include <QStandardPaths>

class FavoritesStorage : public QObject
{
    Q_OBJECT

    public:
        explicit FavoritesStorage(QObject *parent = 0);

        ~FavoritesStorage();

        bool            load();
        bool            save() const;
        bool            add(const int id);
        bool            remove(const int id);
        bool            contains(const int id) const;
        QSet<int>       get() const;

    private:
        QSet<int>      m_favorites;
        QFile          *m_file;

    signals:

    public slots:

};

#endif // FAVORITESSTORAGE_H
