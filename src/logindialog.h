#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#define CONTROLLER_VERSION 1

#include <QDialog>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#ifdef __APPLE__
    #include <QMessageBox>
#endif

#include "serverconnector.h"
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    ServerConnector* GetServerConnector();
    bool IsSuccess();
    static QString GetControllerVersion();

private slots:
    void Login();
    void OnError(QString);
    void OnLoginSuccessed();
    void OnControllerVersionReceived(int, int);

private:
    Ui::LoginDialog *ui;
    ServerConnector *sc;
    bool success = false;
    void LockControls(bool);
    QString GetLoginCachePath();
    void LoadCache(QString json);
};

#endif // LOGINDIALOG_H
