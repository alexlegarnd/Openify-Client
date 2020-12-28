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
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
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
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
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
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
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
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::GetUserInfo(QString username) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_USER_INFO + "?u=" + username);
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
                emit UserInfoReceived(UserInfo(obj));
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::RemoveUser(QString username) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + REMOVE_USER + "?u=" + username);
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
                emit UserRemoved();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::Register(UserInfo info) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + REGISTER);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkReply *reply = NAManager->post(request, info.ToJson().toUtf8());
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::AuthenticationRequiredError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                emit UserRegistered();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::UpdateUser(EditedUser eu) {
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + UPDATE_USER);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    request.setRawHeader("authorization", QString("Bearer " + token).toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QNetworkReply *reply = NAManager->post(request, eu.ToJson().toUtf8());
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::AuthenticationRequiredError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                emit UserRegistered();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

UserInfo ServerConnector::GetLoggedUser()
{
    return loggedUser;
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
                GetLoggedUserInfo();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::GetLoggedUserInfo()
{
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_LOGGED_USER_INFO);
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
                loggedUser = UserInfo(obj);
                emit LoginSuccess();
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
    });
}

void ServerConnector::GetControllerVersion()
{
    auto *NAManager = new QNetworkAccessManager();
    QUrl url (addr + GET_CONTROLLER_VERSION);
    QNetworkRequest request(url);
    if(addr.startsWith("https://")) {
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    }
    QNetworkReply *reply = NAManager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError || reply->error() == QNetworkReply::InternalServerError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = doc.object();
            if (obj["success"].toBool()) {
                emit ControllerVersionReceived(obj["controller-version"].toInt(), obj["minimum-client-version"].toInt());
            } else {
                emit OnError(obj["message"].toString());
            }
        } else {
            emit OnError(reply->errorString());
        }
        reply->deleteLater();
        NAManager->deleteLater();
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
