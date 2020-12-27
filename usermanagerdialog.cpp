#include "usermanagerdialog.h"
#include "ui_usermanagerdialog.h"

UserManagerDialog::UserManagerDialog(ServerConnector *sc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManagerDialog)
{
    ui->setupUi(this);
    this->sc = sc;
    connect(sc, &ServerConnector::UsersListReceived, [=](QVector<QString> users) {
        ui->userList->clear();
        for (QString user : users) {
            ui->userList->addItem(user);
        }
    });
    connect(sc, &ServerConnector::OnError, [=](QString msg) {
        QMessageBox::critical(this, tr("Error"), msg, QMessageBox::Ok);
    });
    connect(ui->quit, &QPushButton::clicked, this, &UserManagerDialog::close);
    sc->GetUsersList();
}

UserManagerDialog::~UserManagerDialog()
{
    delete ui;
}
