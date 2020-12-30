#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#define CLIENT_VERSION "1.0.0.0"

#include <QDialog>

#include "logindialog.h"
#include "serverconnector.h"
#include "aboutinfo.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(ServerConnector *sc, QWidget *parent = nullptr);
    ~AboutDialog();

private slots:
    void OnServerInfoReceived(AboutInfo);
    void OnError(QString);

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
