#ifndef FOLDER_H
#define FOLDER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "file.h"

class Folder
{
private:
    QString name;
    QVector<File> files;
    QVector<Folder> folders;

public:
    Folder() {};
    Folder(QJsonObject);
    QString GetName() const;
    QVector<File> GetFiles() const;
    QVector<Folder> GetFolders() const;
};

#endif // FOLDER_H
