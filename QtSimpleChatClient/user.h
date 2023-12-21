#ifndef USER_H
#define USER_H

#include "baseentity.h"

class User : public BaseEntity
{
public:
    User();

    QString getName() const;
    QString getPassword() const;
    QString getEmail() const;

    void setName(const QString& name);
    void setPassword(const QString& password);
    void setEmail(const QString& email);

private:
    QString Name;
    QString Email;
    QString Password;
    QString ConfirmPassword;
};

#endif // USER_H
