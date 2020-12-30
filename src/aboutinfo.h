#ifndef ABOUTINFO_H
#define ABOUTINFO_H

#include <QString>
#include <QJsonObject>

class AboutInfo
{
private:
    QString OS;
    QString Arch;
    QString GoVersion;
    int MinControllerVersion;
    int CurrentControllerVersion;
    QString ServerVersion;

public:
    AboutInfo(QJsonObject);
    QString GetOS() const;
    QString GetArch() const;
    QString GetGoVersion() const;
    int GetMinControllerVersion() const;
    int GetCurrentControllerVersion() const;
    QString GetServerVersion() const;
};

#endif // ABOUTINFO_H
