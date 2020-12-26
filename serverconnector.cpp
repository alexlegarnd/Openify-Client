#include "serverconnector.h"

ServerConnector::ServerConnector(QString addr, bool ssl)
{
    if (!addr.endsWith("/")) {
        this->addr = addr + "/";
    } else {
        this->addr = addr;
    }
    if (ssl) {
        this->addr = "https://" + this->addr;
    } else {
        this->addr = "http://" + this->addr;
    }
}

void ServerConnector::GetFilesList() {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_FILES_LIST);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                emit ListReceived(Folder(obj));
                reply->deleteLater();
                NAManager->deleteLater();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
    });
}

QString ServerConnector::GetFileURL(int id) {
    return addr + GET_FILE + "?id=" + QString::number(id);;
}

void ServerConnector::GetMetadata(int id) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_METADATA + "?id=" + QString::number(id));
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                emit MetadataReceived(AudioMetadata(obj));
                reply->deleteLater();
                NAManager->deleteLater();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
    });
}
