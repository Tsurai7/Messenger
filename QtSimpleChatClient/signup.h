#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "user.h"
#include "dbmanager.h"

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
signals:
    void userRegistered(const User &user);
private slots:
    void on_pushButton_SignUp_clicked();

    void on_pushButton_SignIn_clicked();

private:
    Ui::SignUp *ui;
    User appUser;
    DbManager *dbManager;
};

#endif // SIGNUP_H
