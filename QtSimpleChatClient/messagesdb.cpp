#include "messagesdb.h"
#include "QDateTime"

MessagesDb::MessagesDb()
{
}

MessagesDb::~MessagesDb()
{
    closeDatabase();
}

bool MessagesDb::openDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("Messages.db");

    if (!m_database.open()) {
        qDebug() << "Error: connection with database failed" << m_database.lastError();
        return false;
    }

    qDebug() << "Database: connection established";
    return true;
}

void MessagesDb::closeDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
        qDebug() << "Database: connection closed";
    }
}

bool MessagesDb::createTable()
{
    if (!m_database.isOpen()) {
        qDebug() << "Error: database is not open";
        return false;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, sender TEXT NOT NULL, text TEXT NOT NULL, timestamp DATETIME NOT NULL)")) {
        qDebug() << "Error: failed to create table" << query.lastError();
        return false;
    }

    qDebug() << "Table created successfully";
    return true;
}

bool MessagesDb::addMessage(const QString& sender, const QString& text)
{
    if (!m_database.isOpen()) {
        qDebug() << "Error: database is not open";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO messages (sender, text, timestamp) VALUES (:sender, :text, :timestamp)");
    query.bindValue(":sender", sender);
    query.bindValue(":text", text);
    query.bindValue(":timestamp", QDateTime::currentDateTime());

    if (!query.exec()) {
        qDebug() << "Error: failed to add message to database" << query.lastError();
        return false;
    }

    qDebug() << "Message added to database";
    return true;
}
