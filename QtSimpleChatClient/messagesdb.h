#ifndef MESSAGESDB_H
#define MESSAGESDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

class MessagesDb
{
public:
    MessagesDb();
    ~MessagesDb();

    bool openDatabase();
    void closeDatabase();
    bool createTable();
    bool addMessage(const QString& sender, const QString& text);

private:
    QSqlDatabase m_database;
};

#endif // MESSAGESDB_H
