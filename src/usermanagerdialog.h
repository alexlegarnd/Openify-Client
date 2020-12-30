#ifndef USERMANAGERDIALOG_H
#define USERMANAGERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>

#include "serverconnector.h"
#include "editeduser.h"

namespace Ui {
class UserManagerDialog;
}

class UserManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagerDialog(ServerConnector *sc, QWidget *parent = nullptr);
    ~UserManagerDialog();

private slots:
    void OnError(QString msg);
    void OnUsersListReceived(QVector<QString> users);
    void OnUserInfoReceived(UserInfo info);
    void OnCurrentItemChanged(QListWidgetItem *item);
    void OnCurrentRowChanged(int i);
    void OnAddButtonClicked();
    void OnRemoveButtonClicked();
    void OnSaveButtonClicked();
    void OnUserRegistered();
    void OnUserRemoved();
    void OnPasswordEdited();
    void OnAdministratorRightEdited();

private:
    Ui::UserManagerDialog *ui;
    ServerConnector *sc;
    bool newUser = false;
    void ClearField();

    bool passworddEdited;
    bool adminRightEdited;
};

#endif // USERMANAGERDIALOG_H
