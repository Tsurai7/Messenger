#include <QApplication>
#include <QFile>

#include "signup.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignUp signUpWindow;
    signUpWindow.show();

    return a.exec();
}
