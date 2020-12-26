#ifndef AUDIOMETADATA_H
#define AUDIOMETADATA_H

#include <QJsonObject>
#include <QString>

class AudioMetadata
{
private:
    QString title;
    QString album;
    QString artist;
    QString albumArtist;
    QString composer;
    int year;
    QString genre;
    QString comment;
    QString codec;
    QString filename;
public:
    AudioMetadata(QJsonObject);
    QString GetTitle() const;
    QString GetAlbum() const;
    QString GetArtist() const;
    QString GetAlbumArtist() const;
    QString GetComposer() const;
    int GetYear() const;
    QString GetGenre() const;
    QString GetComment() const;
    QString GetCodec() const;
    QString GetFilename() const;
};

#endif // AUDIOMETADATA_H
