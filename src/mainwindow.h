#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QGraphicsDropShadowEffect>

#include "serverconnector.h"
#include "folder.h"
#include "file.h"
#include "audiometadata.h"
#include "usermanagerdialog.h"
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ServerConnector *sc, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void GoToFolder(QListWidgetItem *item);
    void PlaySelected(QListWidgetItem *item);
    void AddToSelected();
    void AddFolderToSelected();
    void SetStatus(QMediaPlayer::MediaStatus status);
    void SetState(QMediaPlayer::State state);
    void DurationChanged(qint64 dur);
    void PositionChanged(qint64 pos);
    void SliderMoved(qint64 pos);
    void ChangeState();
    void MetadataReceived(AudioMetadata md);
    void ListReceived(Folder root);
    void OnError(QString error);
    void CurrentMediaChanged(int i);
    void SetCurrentMedia(QListWidgetItem *item);
    void ChangeVolume(int vol);
    void RescanFolder();
    void RefreshList();
    void ShowFileContextMenu(const QPoint &pos);
    void ShowFolderContextMenu(const QPoint &pos);
    void ClearPlaylist();
    void ShowUserManagement();
    void ShowAboutDialog();

private:
    Ui::MainWindow *ui;
    ServerConnector *sc;
    Folder current;
    QVector<Folder> parent;
    QVector<File> queue;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    void UpdateList();
    void GoBack();
    inline void SetPlayButtonIcon(QString status);
    void EnablePlayButton();
    inline void SetIconToButton(QPushButton *b, QString url, QSize s);
    inline void AddFolderToPlaylist(Folder f);
};
#endif // MAINWINDOW_H
