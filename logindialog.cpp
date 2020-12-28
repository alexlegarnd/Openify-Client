#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    sc = new ServerConnector();
    connect(ui->connectButton, &QPushButton::clicked, this, &LoginDialog::Login);
    connect(sc, &ServerConnector::OnError, this, &LoginDialog::OnError);
    connect(sc, &ServerConnector::LoginSuccess, this, &LoginDialog::OnLoginSuccessed);
    connect(sc, &ServerConnector::ControllerVersionReceived, this, &LoginDialog::OnControllerVersionReceived);
    QString cachePath = GetLoginCachePath();
    if (QFile::exists(cachePath)) {
        QFile* file = new QFile(cachePath);
        file->open(QIODevice::ReadOnly);
        auto json = QString(file->readAll());
        file->close();
        delete file;
        LoadCache(json);
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

ServerConnector *LoginDialog::GetServerConnector()
{
    return sc;
}

bool LoginDialog::IsSuccess()
{
    return success;
}

void LoginDialog::Login() {
    QString addr = ui->server->text();
    bool ssl = ui->useSSL->isChecked();
    if (!addr.isEmpty()) {
        sc->SetAddr(addr, ssl);
        ui->errorLabel->setVisible(false);
        LockControls(true);
        sc->GetControllerVersion();
    }
}

void LoginDialog::OnError(QString msg)
{
    ui->errorLabel->setText(msg);
    ui->errorLabel->setVisible(true);
    LockControls(false);
}

void LoginDialog::OnLoginSuccessed()
{
    success = true;
    QJsonObject obj {
        {"server", ui->server->text()},
        {"username", ui->username->text()},
        {"ssl", ui->useSSL->isChecked()}
    };
    QJsonDocument doc(obj);
    QFile *f = new QFile(GetLoginCachePath());
    if (f->open(QIODevice::WriteOnly)) {
        f->write(doc.toJson());
        f->close();
    }
    delete f;
    this->close();
}

void LoginDialog::OnControllerVersionReceived(int v, int min)
{
    if (VERSION >= min) {
        QString username = ui->username->text();
        QString password = ui->password->text();
        LoginInformation info(username, password);
        ui->errorLabel->setVisible(false);
        sc->Login(info);
    } else {
        OnError("This client is too old (Minimal: " + QString::number(min)
                + ", Current: " + QString::number(VERSION) + ")");
    }
}

void LoginDialog::LockControls(bool b) {
    ui->connectButton->setEnabled(!b);
    ui->server->setEnabled(!b);
    ui->username->setEnabled(!b);
    ui->password->setEnabled(!b);
    ui->useSSL->setEnabled(!b);
}

QString LoginDialog::GetLoginCachePath() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir(path).exists()) {
        QDir().mkpath(path);
    }
    path += "/user.cache";
    return path;
}

void LoginDialog::LoadCache(QString json)
{
    QJsonObject obj = QJsonDocument::fromJson(json.toUtf8()).object();
    ui->server->setText(obj["server"].toString());
    ui->username->setText(obj["username"].toString());
    ui->useSSL->setChecked(obj["ssl"].toBool());
    ui->password->setFocus();
}
