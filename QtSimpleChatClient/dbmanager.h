// databaseManager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include "user.h"

class DbManager
{
public:
    DbManager();
    ~DbManager();

    bool createTable();
    void close();

    bool addUser(const QString& name, const QString& password);
    bool getByName(const QString& name, User &user);

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
