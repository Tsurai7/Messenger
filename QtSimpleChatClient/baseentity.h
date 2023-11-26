#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QString>
#include <QDateTime>

class BaseEntity
{
public:
    BaseEntity();
    qint64 getId() const;
    QDateTime getCreatedAt() const;
    QDateTime getUpdatedAt() const;


    void setId(const qint64& id);
    void setCreatedAt(const QDateTime& createdAt);
    void setUpdatedAt(const QDateTime& updatedAt);

private:
    qint64 Id;

    QDateTime CreatedAt;
    QDateTime UpdatedAt;
};

#endif // BASEENTITY_H
