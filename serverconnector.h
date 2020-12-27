#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#define GET_FILES_LIST "api/list/files"
#define GET_FILE "api/get/file"
#define GET_METADATA "api/get/metadata"
#define LOGIN "api/login"
#define RESCAN "api/system/files/scan"
#define USERS_LIST "api/system/user/list"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QObject>


#include "folder.h"
#include "audiometadata.h"
#include "logininformation.h"

class ServerConnector : public QObject
{
    Q_OBJECT

private:
    QString addr;
    QString token;


signals:
    void MetadataReceived(AudioMetadata);
    void ListReceived(Folder);
    void OnError(QString);
    void LoginSuccess();
    void UsersListReceived(QVector<QString>);

public:
    ServerConnector() {};
    ServerConnector(QString addr, bool ssl);
    void GetFilesList();
    void ReScanFolder();
    QUrl GetFileURL(int);
    void GetMetadata(int);
    void Login(LoginInformation info);
    void GetUsersList();

    void SetAddr(QString addr, bool ssl);
    QString GetAddr();
};

#endif // SERVERCONNECTOR_H
