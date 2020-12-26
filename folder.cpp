#include "folder.h"

Folder::Folder(QJsonObject obj)
{
    name = obj["name"].toString();
    for (QJsonValue val : obj["folders"].toArray()) {
        folders.append(Folder(val.toObject()));
    }
    for (QJsonValue val : obj["files"].toArray()) {
        files.append(File(val.toObject()));
    }
}

QString Folder::GetName() const {
    return name;
}

QVector<File> Folder::GetFiles() const {
    return files;
}

QVector<Folder> Folder::GetFolders() const {
    return folders;
}
