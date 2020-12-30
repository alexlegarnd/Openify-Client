#ifndef EDITEDUSER_H
#define EDITEDUSER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class EditedUser
{
private:
    QString username;
    bool passwordEdited;
    bool adminEdited;
    QString password;
    bool administrator;

public:
    EditedUser(QString username, bool pe, bool ae, QString p, bool a);
    QString ToJson();
};

#endif // EDITEDUSER_H
