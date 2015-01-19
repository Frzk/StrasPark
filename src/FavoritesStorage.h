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
