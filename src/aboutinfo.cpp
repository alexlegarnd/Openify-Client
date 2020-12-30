#include "aboutinfo.h"

QString AboutInfo::GetOS() const
{
    return OS;
}

QString AboutInfo::GetArch() const
{
    return Arch;
}

QString AboutInfo::GetGoVersion() const
{
    return GoVersion;
}

int AboutInfo::GetMinControllerVersion() const
{
    return MinControllerVersion;
}

int AboutInfo::GetCurrentControllerVersion() const
{
    return CurrentControllerVersion;
}

QString AboutInfo::GetServerVersion() const
{
    return ServerVersion;
}

AboutInfo::AboutInfo(QJsonObject obj)
{
    OS = obj["os"].toString();
    Arch = obj["arch"].toString();
    GoVersion = obj["go-version"].toString();
    QJsonObject ControllerVersion = obj["controller-version"].toObject();
    MinControllerVersion = ControllerVersion["minimum-client-version"].toInt();
    CurrentControllerVersion = ControllerVersion["controller-version"].toInt();
    ServerVersion = obj["server-version"].toString();
}
