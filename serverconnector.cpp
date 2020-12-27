#include "serverconnector.h"

ServerConnector::ServerConnector(QString addr, bool ssl)
{
    SetAddr(addr, ssl);
}

void ServerConnector::GetFilesList() {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_FILES_LIST);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError) {
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

void ServerConnector::ReScanFolder() {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + RESCAN);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError) {
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

QUrl ServerConnector::GetFileURL(int id) {
    QUrl url(addr + GET_FILE + "?id=" + QString::number(id)
             + "&t=" + token);
    return url;
}

void ServerConnector::GetMetadata(int id) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_METADATA + "?id=" + QString::number(id));
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError) {
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

void ServerConnector::GetUsersList() {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + USERS_LIST);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                QVector<QString> users;
                for (QJsonValue val : obj["users"].toArray()) {
                    users.append(val.toString());
                }
                emit UsersListReceived(users);
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

void ServerConnector::Login(LoginInformation info) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + LOGIN);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkReply *reply = NAManager->post(request, info.ToJson().toUtf8());
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::AuthenticationRequiredError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                token = obj["token"].toString();
                emit LoginSuccess();
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

void ServerConnector::SetAddr(QString addr, bool ssl)
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

QString ServerConnector::GetAddr()
{
    return addr;
}
