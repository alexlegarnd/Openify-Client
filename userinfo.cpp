#include "userinfo.h"

UserInfo::UserInfo(QJsonObject obj)
{
    username = obj["username"].toString();
    administrator = obj["administrator"].toBool();
}

UserInfo::UserInfo(QString username, QString password, bool administrator) {
    this->username = username;
    this->password = password;
    this->administrator = administrator;
}

QString UserInfo::GetUsername()
{
    return username;
}

bool UserInfo::IsAdministrator()
{
    return administrator;
}

QString UserInfo::ToJson() {
    QJsonObject obj {
        {"username", username},
        {"password", password},
        {"administrator", administrator}
    };
    QJsonDocument doc(obj);
    return doc.toJson();
}
