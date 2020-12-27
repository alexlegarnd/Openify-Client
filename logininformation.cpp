#include "logininformation.h"

LoginInformation::LoginInformation(QString username, QString password)
{
    this->username = username;
    this->password = password;
}

QString LoginInformation::ToJson() {
    QJsonObject obj;
    obj["username"] = username;
    obj["password"] = password;
    QJsonDocument doc(obj);
    return doc.toJson();
}
