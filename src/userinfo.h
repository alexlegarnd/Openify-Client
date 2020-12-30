#ifndef USERINFO_H
#define USERINFO_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

class UserInfo
{
private:
    QString username;
    QString password;
    bool administrator = false;

public:
    UserInfo() {};
    UserInfo(QJsonObject obj);
    UserInfo(QString username, QString password, bool administrator);
    QString GetUsername();
    bool IsAdministrator();
    QString ToJson();
};

#endif // USERINFO_H
