#include "audiometadata.h"

QString AudioMetadata::GetTitle() const
{
    if (title.isEmpty()) {
        return filename;
    }
    return title;
}

QString AudioMetadata::GetAlbum() const
{
    if (album.isEmpty()) {
        return "?";
    }
    return album;
}

QString AudioMetadata::GetArtist() const
{
    if (artist.isEmpty()) {
        return "?";
    }
    return artist;
}

QString AudioMetadata::GetAlbumArtist() const
{
    return albumArtist;
}

QString AudioMetadata::GetComposer() const
{
    return composer;
}

int AudioMetadata::GetYear() const
{
    return year;
}

QString AudioMetadata::GetGenre() const
{
    return genre;
}

QString AudioMetadata::GetComment() const
{
    return comment;
}

QString AudioMetadata::GetCodec() const
{
    return codec;
}

QString AudioMetadata::GetFilename() const
{
    return filename;
}

AudioMetadata::AudioMetadata(QJsonObject obj)
{
    title = obj["title"].toString();
    album = obj["album"].toString();
    artist = obj["artist"].toString();
    albumArtist = obj["album-artist"].toString();
    composer = obj["composer"].toString();
    year = obj["year"].toInt();
    genre = obj["genre"].toString();
    comment = obj["comment"].toString();
    codec = obj["codec"].toString();
    filename = obj["filename"].toString();
}

