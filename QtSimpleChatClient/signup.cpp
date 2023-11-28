#include "signup.h"
#include "ui_signup.h"

#include <QMessageBox>
#include <QLineEdit>
#include "QRegularExpression"

#include "signin.h"
#include "chatwindow.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    setFixedSize(480, 480);

    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_Confirm->setEchoMode(QLineEdit::Password);
     dbManager = new DbManager();
    //dbManager->createTable();

}

SignUp::~SignUp()
{
    delete ui;
    dbManager->close();
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
        QMessageBox::warning(this, "Error", "Enter vallid email");
        return;
    }

    if (password != confirmPassword)
    {
        QMessageBox::warning(this, "Error", "Passwords are not the same");
        return;
    }

    if (password.length() < 6)
    {
        QMessageBox::warning(this, "Error", "Password length should be longer than 6");
        return;
    }

    User testUser;
    if (dbManager->getByEmail(email, testUser))
    {
        QMessageBox::warning(this, "Error", "Email is taken, try to sign in");
        return;
    }

    User user;
    user.setEmail(email);
    user.setName(username);
    user.setPassword(password);
    user.setCreatedAt(QDateTime::currentDateTime());

    if (dbManager->addUser(user))
    {
        if (dbManager->getByName(username, user))
        {
            //emit userRegistered(user);
            qDebug() << "Emitting userRegistered signal with user:" << user.getName();
            //this->accept();
            ChatWindow* chatWindow = new ChatWindow();

            this->close();

            chatWindow->show();

        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось получить информацию о пользователе.");
        }
    }

}


void SignUp::on_pushButton_SignIn_clicked()
{
    SignIn *signinWindow = new SignIn(this);

    this->close();

    signinWindow->show();
}

