#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    LoginDialog d;
    d.exec();
    if (d.IsSuccess()) {
        MainWindow w(d.GetServerConnector());
        w.show();
        return a.exec();
    } else {
        ServerConnector *sc = d.GetServerConnector();
        delete sc;
    }

    return 0;
}
