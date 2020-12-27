#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

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

public slots:
    void Login();
    void OnError(QString);
    void OnLoginSuccessed();

private:
    Ui::LoginDialog *ui;
    ServerConnector *sc;
    bool success;
    void LockControls(bool);
    QString GetLoginCachePath();
    void LoadCache(QString json);
};

#endif // LOGINDIALOG_H
