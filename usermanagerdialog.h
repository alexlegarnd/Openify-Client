#ifndef USERMANAGERDIALOG_H
#define USERMANAGERDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "serverconnector.h"

namespace Ui {
class UserManagerDialog;
}

class UserManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagerDialog(ServerConnector *sc, QWidget *parent = nullptr);
    ~UserManagerDialog();

private:
    Ui::UserManagerDialog *ui;
    ServerConnector *sc;
};

#endif // USERMANAGERDIALOG_H
