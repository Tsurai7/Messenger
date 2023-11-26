#include "dbmanager.h"

#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


DbManager::DbManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Users.db");
    database.open();
}

bool DbManager::createTable()
{
    if (!database.open()) {
        qDebug() << "Error: Unable to open database." << database.lastError();
        return false;
    }

    QSqlQuery createTableQuery;
    createTableQuery.prepare("CREATE TABLE IF NOT EXISTS users "
                             "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "username TEXT, "
                             "password TEXT, "
                             "createdAt DATETIME, "
                             "updatedAt DATETIME)");

    if (!createTableQuery.exec()) {
        qDebug() << "Error: Unable to create table." << createTableQuery.lastError();
        return false;
    }

    return true;
}

void DbManager::close()
{
    database.close();
}

bool DbManager::addUser(const QString &username, const QString &password)
{
    if (!database.isOpen()) {
        qDebug() << "Error: Database is not open.";
        return false;
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, createdAt, updatedAt) "
                  "VALUES (:username, :password, :createdAt, :updatedAt)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":createdAt", currentDateTime);
    query.bindValue(":updatedAt", currentDateTime);

    if (!query.exec()) {
        qDebug() << "Error: Unable to add user." << query.lastError();
        return false;
    }

    return true;
}


bool DbManager::getByName(const QString &username, User &user)
{

    if (!database.isOpen()) {
        database.open();
    }

    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to retrieve user." << query.lastError();
        return false;
    }

    if (query.next()) {
        user.setId(query.value("id").toInt());
        user.setName(query.value("username").toString());
        user.setPassword(query.value("password").toString());
        user.setCreatedAt(query.value("createdAt").toDateTime());
        user.setUpdatedAt(query.value("updatedAt").toDateTime());
        return true;
    }

    return false;
}

