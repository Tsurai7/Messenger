#include <QApplication>
#include <QFile>

#include "signup.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignUp signUpWindow;
    signUpWindow.show();

    QFile styleFile(":/stylesheets/style.css");

    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QString styleSheet = styleFile.readAll();

        qApp->setStyleSheet(styleSheet);

        styleFile.close();
    } else {
        qDebug() << "Failed to open stylesheet file";
    }

    return a.exec();
}
