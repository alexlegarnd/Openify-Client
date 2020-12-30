#ifndef LOGININFORMATION_H
#define LOGININFORMATION_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class LoginInformation
{
private:
    QString username;
    QString password;
public:
    LoginInformation(QString username, QString password);
    QString ToJson();
};

#endif // LOGININFORMATION_H
