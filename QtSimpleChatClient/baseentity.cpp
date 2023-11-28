#include "baseentity.h"

BaseEntity::BaseEntity()
{
}

qint64 BaseEntity::getId() const
{
    return Id;
}

QDateTime BaseEntity::getCreatedAt() const
{
    return CreatedAt;
}

QDateTime BaseEntity::getUpdatedAt() const
{
    return UpdatedAt;
}

void BaseEntity::setId(const qint64& id)
{
    Id = id;
}

void BaseEntity::setCreatedAt(const QDateTime& createdAt)
{
    CreatedAt = createdAt;
}

void BaseEntity::setUpdatedAt(const QDateTime& updatedAt)
{
    UpdatedAt = updatedAt;
}
