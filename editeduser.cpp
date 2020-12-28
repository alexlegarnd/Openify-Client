#include "editeduser.h"

EditedUser::EditedUser(QString username, bool pe, bool ae, QString p, bool a)
{
    this->username = username;
    this->passwordEdited = pe;
    this->adminEdited = ae;
    this->password = p;
    this->administrator = a;
}

QString EditedUser::ToJson()
{
    QJsonObject obj {
        {"username", username},
        {"password-edited", passwordEdited},
        {"administrator-edited", adminEdited},
        {"password", password},
        {"administrator", administrator}
    };

    QJsonDocument doc(obj);
    return doc.toJson();
}
