#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_SignIn_clicked();

private:
    Ui::SignIn *ui;
    DbManager *dbManager;
};

#endif // SIGNIN_H
