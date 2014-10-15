#include "window.h"

Window::Window(QWidget *parent) :
    QDialog(parent)
{
    thread = new QThread();
    vk = new VKMusic();
    downloader = new MusicDownloader();
    this->setLayout(new QVBoxLayout);
    authWidget = new AuthWidget(this);
    settingsWidget = new SettingsWidget(this);
    this->layout()->addWidget(authWidget);
    this->setFixedSize(300, 200);
    createMenu();
    connect(authWidget->btnLogin, SIGNAL(clicked()), this, SLOT(Authorization()));

    connect(thread, SIGNAL(started()), downloader, SLOT(process()));
    connect(downloader, SIGNAL(finished()), this, SLOT(DownloadEnd()));
    connect(downloader, SIGNAL(finished()), thread, SLOT(quit()));
}

void Window::createMenu()
{
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * menuFile = menuBar->addMenu("File");
    QAction * actSettings   = menuFile->addAction("Settings");
    QAction * actExit       = menuFile->addAction("Exit");

    QObject::connect(actSettings, SIGNAL(triggered()), this, SLOT(OpenSettings()));
    QObject::connect(actExit, SIGNAL(triggered()), this, SLOT(Exit()));

    this->layout()->setMenuBar(menuBar);
}


void Window::Authorization()
{
    if(vk == NULL)
        vk = new VKMusic();
    vk->setClientId("4561989");

    std::string login = authWidget->leLogin->text().toStdString();
    std::string password = authWidget->lePassword->text().toStdString();

    if(login.empty() || password.empty())
    {
        QMessageBox::warning(this, "Error", "Login or password is invalid");
        return;
    }

    vk->setLogin(login);
    vk->setPassword(password);
    vk->parseMusic();

    /*
     *  If not errors, auth success
     */
    if(!vk->getLastError().b)
    {
        this->setFixedSize(300, 400);
        musicList = new MusicList(this);
        downloader->setOutputTrackLabel(musicList->lblDownloadMusicTitle);
        connect(musicList->btnDownload, SIGNAL(clicked()), this, SLOT(Download()));

        delete authWidget;
        authWidget = NULL;

        std::vector<VKMusic::Song> music = vk->getMusic();
        for(std::vector<VKMusic::Song>::iterator it = music.begin(); it != music.end(); it++)
        {
            QString MusicTitle = QString::fromStdString((*it).artist) + " - " + QString::fromStdString((*it).title);
            QListWidgetItem * item = new QListWidgetItem(MusicTitle, musicList->musicList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, QString::fromStdString((*it).url));
            musicList->musicList->addItem(item);
        }
        this->layout()->addWidget(musicList);
    }else{
        QMessageBox::warning(this, "Auth Error", "Login or password is invalid!" );
    }
}

void Window::Download()
{
    if(vk == NULL) return;


    std::string path = Settings::init()->getJson()["settings"]["save_path"].asString();
    bool replace = Settings::init()->getJson()["settings"]["replace_existing_files"].asBool();
    std::vector<std::pair<std::string, std::string> > tracks;

    for(int i = 0; i < musicList->musicList->count(); ++i)
    {
        QListWidgetItem* item = musicList->musicList->item(i);
        if(item->checkState() == Qt::Unchecked) continue;
        std::string url = vk->parseMusicLink(item->data(Qt::UserRole).toString().toStdString());
        std::string filename = item->text().toStdString();
        filename += ".mp3";
        tracks.push_back(std::make_pair(url, filename));
    }
    downloader->setMusicList(tracks);
    downloader->setPath(path);
    downloader->setReplace(replace);

    downloader->moveToThread(thread);

    thread->start();

    musicList->StartLoadAnim();
}

void Window::DownloadEnd()
{
    QMessageBox::warning(this, "OK", "Download is end");
    musicList->lblDownloadMusicTitle->setText("");
    musicList->StopLoadAnim();
}

void Window::OpenSettings()
{
    if(settingsWidget != NULL)
        settingsWidget->show();
    // else print error
}


void Window::Exit()
{
    exit(0);
}















