#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ServerConnector *sc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    ui->volume->setValue(player->volume());
    this->sc = sc;
    ui->actionRescan_folder->setEnabled(sc->GetLoggedUser().IsAdministrator());
    connect(sc, &ServerConnector::MetadataReceived, this, &MainWindow::MetadataReceived);
    connect(sc, &ServerConnector::ListReceived, this, &MainWindow::ListReceived);
    connect(sc, &ServerConnector::OnError, this, &MainWindow::OnError);
    connect(ui->foldersList, &QListWidget::itemDoubleClicked, this, &MainWindow::GoToFolder);
    connect(ui->filesList, &QListWidget::itemDoubleClicked, this, &MainWindow::PlaySelected);
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::ChangeState);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &MainWindow::SliderMoved);
    connect(ui->currentList, &QListWidget::itemDoubleClicked, this, &MainWindow::SetCurrentMedia);
    connect(ui->volume, &QSlider::sliderMoved, this, &MainWindow::ChangeVolume);
    connect(ui->actionRescan_folder, &QAction::triggered, this, &MainWindow::RescanFolder);
    connect(ui->actionRefresh_list, &QAction::triggered, this, &MainWindow::RefreshList);
    connect(ui->actionUser_Management, &QAction::triggered, this, &MainWindow::ShowUserManagement);
    connect(ui->filesList, &QListWidget::customContextMenuRequested, this, &MainWindow::ShowFileContextMenu);
    connect(ui->clearPlaylist, &QPushButton::clicked, this, &MainWindow::ClearPlaylist);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::CurrentMediaChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::SetStatus);
    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::SetState);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::DurationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::PositionChanged);
    ui->filesList->setContextMenuPolicy(Qt::CustomContextMenu);
    SetPlayButtonIcon("PLAY");
    sc->GetFilesList();
    ui->statusBar->showMessage("Loading files list...");
}

MainWindow::~MainWindow()
{
    delete playlist;
    delete player;
    delete sc;
    delete ui;
}

void MainWindow::UpdateList() {
    ui->filesList->clear();
    ui->foldersList->clear();
    for(File file : current.GetFiles()) {
        ui->filesList->addItem(file.GetName());
    }
    if (current.GetName() != "/") {
        ui->foldersList->addItem("..");
    }
    for(Folder folder : current.GetFolders()) {
        ui->foldersList->addItem(folder.GetName());
    }
}

void MainWindow::GoToFolder(QListWidgetItem *item) {
    QString name = item->text();
    if (name == "..") {
        GoBack();
    } else {
        parent.append(current);
        for(Folder folder : current.GetFolders()) {
            if (folder.GetName() == name) {
                current = folder;
            }
        }
    }
    UpdateList();
}

void MainWindow::GoBack() {
    current = parent.last();
    parent.removeLast();
}

void MainWindow::PlaySelected(QListWidgetItem *item) {
    QString name = item->text();
    for(File file : current.GetFiles()) {
        if (file.GetName() == name) {
            queue.append(file);
            ui->currentList->addItem(file.GetName());
            playlist->addMedia(sc->GetFileURL(file.GetId()));
            playlist->setCurrentIndex(queue.size() - 1);
            player->play();
        }
    }
    EnablePlayButton();
}

void MainWindow::AddToSelected()
{
    for (QListWidgetItem *item : ui->filesList->selectedItems()) {
        QString name = item->text();
        for(File file : current.GetFiles()) {
            if (file.GetName() == name) {
                queue.append(file);
                ui->currentList->addItem(file.GetName());
                playlist->addMedia(sc->GetFileURL(file.GetId()));
            }
        }
    }
    EnablePlayButton();
}

void MainWindow::ShowFileContextMenu(const QPoint &pos) {
    QPoint globalPos = ui->filesList->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Add to playlist", this, &MainWindow::AddToSelected);
    menu.exec(globalPos);
}

void MainWindow::ClearPlaylist()
{
    player->stop();
    playlist->clear();
    queue.clear();
    ui->currentList->clear();
    EnablePlayButton();
}

void MainWindow::ShowUserManagement()
{
    UserManagerDialog d(sc);
    d.exec();
}

void MainWindow::SetPlayButtonIcon(QString status) {
    ui->playButton->setText("");
    ui->playButton->setIcon(QIcon(":/icons/pictures/" + status + ".png"));
    ui->playButton->setIconSize(QSize(48, 48));
}

void MainWindow::SetStatus(QMediaPlayer::MediaStatus status) {
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus : {
        ui->statusBar->showMessage("The status of the media cannot be determined.");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    case QMediaPlayer::NoMedia : {
        ui->statusBar->showMessage("Stopped");
        ui->mediaTitle->setText("Nothing playing");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    case QMediaPlayer::LoadingMedia : {
        ui->statusBar->showMessage("Loading...");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    case QMediaPlayer::LoadedMedia : {
        ui->statusBar->showMessage("Ready");

        ui->horizontalSlider->setEnabled(true);
        break;
    }
    case QMediaPlayer::StalledMedia : {
        ui->statusBar->showMessage("Buffering...");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    case QMediaPlayer::BufferingMedia : {
        ui->statusBar->showMessage("Buffering...");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    case QMediaPlayer::BufferedMedia : {
        ui->statusBar->showMessage("Buffered");
        ui->horizontalSlider->setEnabled(true);
        break;
    }
    case QMediaPlayer::EndOfMedia : {
        ui->statusBar->showMessage("Stopped");
        ui->horizontalSlider->setEnabled(true);
        break;
    }
    case QMediaPlayer::InvalidMedia : {
        ui->statusBar->showMessage("The current media cannot be played.");
        ui->horizontalSlider->setEnabled(false);
        break;
    }
    }
}

void MainWindow::SetState(QMediaPlayer::State state) {
    if (state == QMediaPlayer::PlayingState) {
        SetPlayButtonIcon("PAUSE");
    } else {
        SetPlayButtonIcon("PLAY");
    }
}

void MainWindow::DurationChanged(qint64 dur)
{
    ui->horizontalSlider->setMaximum(dur);
}

void MainWindow::PositionChanged(qint64 pos)
{
    ui->horizontalSlider->setValue(pos);
    ui->timeStatus->setText(QDateTime::fromTime_t(pos/1000).toUTC().toString("hh:mm:ss"));
}

void MainWindow::SliderMoved(qint64 pos)
{
    player->setPosition(pos);
}

void MainWindow::ChangeState() {
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::MetadataReceived(AudioMetadata md)
{
    ui->mediaTitle->setText(md.GetTitle());
    ui->album->setText(md.GetAlbum());
    ui->artist->setText(md.GetArtist());
    ui->albumArtist->setText(md.GetAlbumArtist());
    ui->composer->setText(md.GetComposer());
    ui->year->setNum(md.GetYear());
    ui->genre->setText(md.GetGenre());
    ui->comment->setText(md.GetComment());
    ui->codec->setText(md.GetCodec());
    ui->filename->setText(md.GetFilename());
}

void MainWindow::ListReceived(Folder root)
{
    current = root;
    UpdateList();
    ui->statusBar->showMessage("Files list loaded!", 3000);
}

void MainWindow::OnError(QString error)
{
    ui->statusBar->showMessage(error);
}

void MainWindow::CurrentMediaChanged(int i)
{
    ui->currentList->clear();
    for (int x = 0; x < queue.size(); x++) {
        if (x == i) {
            ui->currentList->addItem("> " + queue[x].GetName());
            sc->GetMetadata(queue[x].GetId());
        } else {
            ui->currentList->addItem(queue[x].GetName());
        }
    }
}

void MainWindow::SetCurrentMedia(QListWidgetItem *item)
{
    playlist->setCurrentIndex(ui->currentList->row(item));
}

void MainWindow::ChangeVolume(int vol)
{
    player->setVolume(vol);
}

void MainWindow::RescanFolder()
{
    if (sc->GetLoggedUser().IsAdministrator()) {
        sc->ReScanFolder();
    }
}

void MainWindow::RefreshList()
{
    sc->GetFilesList();
}

void MainWindow::EnablePlayButton() {
    ui->playButton->setEnabled(queue.size() > 0);
}
