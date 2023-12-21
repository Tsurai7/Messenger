#include "signin.h"
#include "ui_signin.h"
#include "signup.h"
#include "chatwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include "QRegularExpression"

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    setFixedSize(400, 440);
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    dbManager = new DbManager();
}

SignIn::~SignIn()
{
    delete ui;
    dbManager->close();
}

void SignIn::on_pushButton_Back_clicked()
{
    SignUp *signUpWindow = new SignUp(this);
    this->close();
    signUpWindow->show();
}


void SignIn::on_pushButton_SignIn_clicked()
{
    QString email = ui->lineEdit_Email->text();
    QString password = ui->lineEdit_Password->text();

    // model validation
    if (email.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Fill all fields");
        return;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");

    if (!emailRegex.match(email).hasMatch())
    {
        QMessageBox::warning(this, "Error", "Enter valid email.");
        return;
    }

    if (password.length() < 6)
    {
        QMessageBox::warning(this, "Error", "Password should be longer than 6");
        return;
    }

    User testUser;
    if(!dbManager->getByEmail(email, testUser))
    {
        QMessageBox::warning(this, "Error", "Email is not signed up yet. Try to sign up");
        return;
    }

    User user;
    if (dbManager->getByEmail(email, user))
    {
        if(email == user.getEmail() && password == user.getPassword())
        {
            ChatWindow* chatWindow = new ChatWindow();
            this->close();
            chatWindow->show();
        }
        else
        {
            QMessageBox::warning(this, "Error", "Wrong credentials");
            return;
        }
    }
}

