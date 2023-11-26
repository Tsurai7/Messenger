#include "user.h"

User::User()
{
}

QString User::getName() const
{
    return Name;
}

QString User::getPassword() const
{
    return Password;
}

QString User::getEmail() const
{
    return Email;
}

void User::setName(const QString& name)
{
    Name = name;
}

void User::setPassword(const QString& password)
{
    Password = password;
}

void User::setEmail(const QString& email)
{
    Email = email;
}
