#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QJsonObject>

class File
{
private:
    QString name;
    QString ext;
    int id;

public:
    File(QJsonObject);
    QString GetName() const;
    QString GetExt() const;
    int GetId() const;
};

#endif // FILE_H
