#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include "QRegularExpression"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_SignUp_clicked()
{
    QString username = ui->lineEdit_Name->text();
    QString email = ui->lineEdit_Email->text();
    QString password = ui->lineEdit_Password->text();
    QString confirmPassword = ui->lineEdit_Confirm->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    if (!emailRegex.match(email).hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректный email.");
        return;
    }

    if (password != confirmPassword)
    {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    if (password.length() < 6)
    {
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать не менее 6 символов.");
        return;
    }

    if (dbManager->addUser(username, password))
    {
        User user = User();
        if (dbManager->getByName(username, user))
        {
            emit userRegistered(user);
            qDebug() << "Emitting userRegistered signal with user:" << user.getName();
            this->accept();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось получить информацию о пользователе.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить пользователя. Пожалуйста, попробуйте еще раз.");
    }
}



