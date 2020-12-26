#include "file.h"

File::File(QJsonObject obj)
{
    name = obj["name"].toString();
    ext = obj["ext"].toString();
    id = obj["id"].toInt();
}

QString File::GetName() const {
    return name;
}

QString File::GetExt() const {
    return ext;
}

int File::GetId() const {
    return id;
}
