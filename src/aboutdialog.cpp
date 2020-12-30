#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(ServerConnector *sc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->version->setText(QString("Client version: %1").arg(CLIENT_VERSION));
    QString sysInfo = QString("System information: %1 build %2 (%3 %4)")
            .arg(QSysInfo::prettyProductName())
            .arg(QSysInfo::kernelVersion())
            .arg(QSysInfo::kernelType())
            .arg(QSysInfo::buildCpuArchitecture());
    ui->system_info->setText(sysInfo);
    ui->compatible_controller_version->setText(QString("Internal controller version (Server Connector): %1")
                                               .arg(LoginDialog::GetControllerVersion()));
    connect(sc, &ServerConnector::ServerAboutReceived, this, &AboutDialog::OnServerInfoReceived);
    connect(sc, &ServerConnector::OnError, this, &AboutDialog::OnError);
    sc->GetServerAbout();

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::OnServerInfoReceived(AboutInfo ai)
{
    ui->arch->setText("Arch: " + ai.GetArch());
    ui->os->setText("OS: " + ai.GetOS());
    ui->go_version->setText("Go Version: " + ai.GetGoVersion());
    ui->min_controller_version->setText("Minimum controller version: " + QString::number(ai.GetMinControllerVersion()));
    ui->current_controller_version->setText("Controller version: " + QString::number(ai.GetCurrentControllerVersion()));
    ui->server_version->setText("Server version: " + ai.GetServerVersion());
}

void AboutDialog::OnError(QString msg)
{
    ui->arch->setText("Error: " + msg);
}

