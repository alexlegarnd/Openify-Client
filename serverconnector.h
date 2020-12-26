#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#define GET_FILES_LIST "api/list/files"
#define GET_FILE "api/get/file"
#define GET_METADATA "api/get/metadata"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QObject>

#include "folder.h"
#include "audiometadata.h"

class ServerConnector : public QObject
{
    Q_OBJECT

private:
    QString addr;


signals:
    void MetadataReceived(AudioMetadata);
    void ListReceived(Folder);
    void OnError(QString);

public:
    ServerConnector() {};
    ServerConnector(QString addr, bool ssl);
    void GetFilesList();
    QString GetFileURL(int);
    void GetMetadata(int);
};

#endif // SERVERCONNECTOR_H
