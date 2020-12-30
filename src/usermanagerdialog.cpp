#include "usermanagerdialog.h"
#include "ui_usermanagerdialog.h"

UserManagerDialog::UserManagerDialog(ServerConnector *sc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManagerDialog)
{
    ui->setupUi(this);
    this->sc = sc;
    if (sc->GetLoggedUser().IsAdministrator()) {
        ui->add->setEnabled(true);
    }
    connect(sc, &ServerConnector::UsersListReceived, this, &UserManagerDialog::OnUsersListReceived);
    connect(sc, &ServerConnector::OnError, this, &UserManagerDialog::OnError);
    connect(sc, &ServerConnector::UserInfoReceived, this, &UserManagerDialog::OnUserInfoReceived);
    connect(ui->userList, &QListWidget::currentItemChanged, this, &UserManagerDialog::OnCurrentItemChanged);
    connect(ui->userList, &QListWidget::currentRowChanged, this, &UserManagerDialog::OnCurrentRowChanged);
    connect(ui->quit, &QPushButton::clicked, this, &UserManagerDialog::close);
    connect(ui->add, &QPushButton::clicked, this, &UserManagerDialog::OnAddButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &UserManagerDialog::OnSaveButtonClicked);
    connect(sc, &ServerConnector::UserRegistered, this, &UserManagerDialog::OnUserRegistered);
    connect(sc, &ServerConnector::UserRemoved, this, &UserManagerDialog::OnUserRemoved);
    connect(ui->remove, &QPushButton::clicked, this, &UserManagerDialog::OnRemoveButtonClicked);
    connect(sc, &ServerConnector::UserEdited, this, &UserManagerDialog::OnUserRegistered);
    connect(ui->password, &QLineEdit::textChanged, this, &UserManagerDialog::OnPasswordEdited);
    connect(ui->admin, &QCheckBox::stateChanged, this, &UserManagerDialog::OnAdministratorRightEdited);
    sc->GetUsersList();
}

UserManagerDialog::~UserManagerDialog()
{
    delete ui;
}

void UserManagerDialog::OnError(QString msg)
{
    QMessageBox::critical(this, tr("Error"), msg, QMessageBox::Ok);
}

void UserManagerDialog::OnUsersListReceived(QVector<QString> users)
{
    ClearField();
    ui->userList->clear();
    for (QString user : users) {
        ui->userList->addItem(user);
    }
}

void UserManagerDialog::OnUserInfoReceived(UserInfo info)
{
    newUser = false;
    ClearField();
    ui->saveButton->setEnabled(false);
    ui->username->setEnabled(false);
    ui->username->setText(info.GetUsername());
    ui->admin->setChecked(info.IsAdministrator());
    ui->admin->setEnabled(sc->GetLoggedUser().IsAdministrator());
    ui->password->setEnabled((sc->GetLoggedUser().GetUsername() == info.GetUsername()
            || sc->GetLoggedUser().IsAdministrator()));
}

void UserManagerDialog::OnCurrentItemChanged(QListWidgetItem *item)
{
    if (item != nullptr) {
        sc->GetUserInfo(item->text());
    }
}

void UserManagerDialog::OnCurrentRowChanged(int i)
{
    if (sc->GetLoggedUser().IsAdministrator() && i >= 0) {
        ui->remove->setEnabled(true);
    }
}

void UserManagerDialog::OnAddButtonClicked()
{
    newUser = true;
    ClearField();
    ui->saveButton->setEnabled(true);
    ui->username->setEnabled(true);
    ui->password->setEnabled(true);
    ui->admin->setChecked(false);
    ui->admin->setEnabled(sc->GetLoggedUser().IsAdministrator());
}

void UserManagerDialog::OnRemoveButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Delete this user");
    msgBox.setInformativeText("This action cannot be undone. Are you sure you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
        QList<QListWidgetItem*> items = ui->userList->selectedItems();
        if (items.size() > 0) {
            QString text = items[0]->text();
            sc->RemoveUser(text);
        }
    }
}

void UserManagerDialog::OnSaveButtonClicked()
{
    if (newUser) {
        if (!ui->username->text().isEmpty() && !ui->password->text().isEmpty()) {
            UserInfo i(ui->username->text(), ui->password->text(), ui->admin->isChecked());
            sc->Register(i);
        }
    } else {
        EditedUser eu(ui->username->text(),passworddEdited, adminRightEdited,
                      ui->password->text(), ui->admin->isChecked());
        sc->UpdateUser(eu);
    }
}

void UserManagerDialog::OnUserRegistered()
{
    newUser = false;
    sc->GetUsersList();
    sc->GetUserInfo(ui->username->text());
}

void UserManagerDialog::OnUserRemoved()
{
    newUser = false;
    ClearField();
    sc->GetUsersList();
}

void UserManagerDialog::OnPasswordEdited()
{
    if (!newUser) {
        passworddEdited = true;
        ui->saveButton->setEnabled(true);
    }
}

void UserManagerDialog::OnAdministratorRightEdited()
{
    if (!newUser) {
        adminRightEdited = true;
        ui->saveButton->setEnabled(true);
    }
}

void UserManagerDialog::ClearField() {
    ui->username->clear();
    ui->password->clear();
    ui->admin->setChecked(false);
}
