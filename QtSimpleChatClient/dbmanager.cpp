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
                             "email TEXT, "
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

bool DbManager::addUser(User user)
{
    if (!database.isOpen()) {
        qDebug() << "Error: Database is not open.";
        return false;
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, email, password, createdAt, updatedAt) "
                  "VALUES (:username, :email, :password, :createdAt, :updatedAt)");
    query.bindValue(":username", user.getName());
    query.bindValue(":email", user.getEmail());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":createdAt", currentDateTime);
    query.bindValue(":updatedAt", currentDateTime);

    if (!query.exec()) {
        qDebug() << "Error: Unable to add user." << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::getByEmail(const QString &email, User &user)
{
    if (!database.isOpen()) {
        database.open();
    }

    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Error: Unable to retrieve user by email." << query.lastError();
        return false;
    }

    if (query.next()) {
        user.setId(query.value("id").toInt());
        user.setName(query.value("username").toString());
        user.setEmail(query.value("email").toString()); // Добавлено получение email
        user.setPassword(query.value("password").toString());
        user.setCreatedAt(query.value("createdAt").toDateTime());
        user.setUpdatedAt(query.value("updatedAt").toDateTime());
        return true;
    }

    return false;
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

