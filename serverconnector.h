#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#define GET_FILES_LIST "api/list/files"
#define GET_FILE "api/get/file"
#define GET_METADATA "api/get/metadata"
#define LOGIN "api/login"
#define RESCAN "api/system/files/scan"
#define USERS_LIST "api/system/user/list"
#define GET_USER_INFO "api/system/user/get"
#define GET_LOGGED_USER_INFO "api/system/user/me"
#define GET_CONTROLLER_VERSION "api/system/controller/version"
#define REGISTER "api/system/user/register"
#define REMOVE_USER "api/system/user/remove"
#define UPDATE_USER "api/system/user/update"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QObject>


#include "folder.h"
#include "audiometadata.h"
#include "logininformation.h"
#include "userinfo.h"
#include "editeduser.h"

class ServerConnector : public QObject
{
    Q_OBJECT

private:
    QString addr;
    QString token;
    UserInfo loggedUser;
    void GetLoggedUserInfo();


signals:
    void MetadataReceived(AudioMetadata);
    void ListReceived(Folder);
    void OnError(QString);
    void LoginSuccess();
    void UsersListReceived(QVector<QString>);
    void UserInfoReceived(UserInfo);
    void ControllerVersionReceived(int v, int min);
    void UserRegistered();
    void UserRemoved();
    void UserEdited();

public:
    ServerConnector() {};
    ServerConnector(QString addr, bool ssl);
    void GetFilesList();
    void ReScanFolder();
    QUrl GetFileURL(int);
    void GetMetadata(int);
    void Login(LoginInformation info);
    void GetUsersList();
    void GetUserInfo(QString username);
    UserInfo GetLoggedUser();
    void GetControllerVersion();
    void Register(UserInfo);
    void RemoveUser(QString);
    void UpdateUser(EditedUser eu);


    void SetAddr(QString addr, bool ssl);
    QString GetAddr();
};

#endif // SERVERCONNECTOR_H
