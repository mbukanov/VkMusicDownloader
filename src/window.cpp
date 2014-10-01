#include "window.h"

Window::Window(QWidget *parent) :
    QDialog(parent)
{
    vk = new VKapi;
    this->setLayout(new QVBoxLayout);
    authWidget = new AuthWidget(this);
    this->layout()->addWidget(authWidget);
    createMenu();
    connect(authWidget->btnLogin, SIGNAL(clicked()), this, SLOT(Authorization()));
}

void Window::createMenu()
{
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * menuFile = menuBar->addMenu("File");
    QAction * actSavePath   = menuFile->addAction("Set save path");
    QAction * actExit       = menuFile->addAction("Exit");

    QObject::connect(actSavePath, SIGNAL(triggered()), this, SLOT(ChooseSaveDirectory()));
    QObject::connect(actExit, SIGNAL(triggered()), this, SLOT(Exit()));

    this->layout()->setMenuBar(menuBar);
}

void Window::Authorization()
{
    if(vk == NULL)
        vk = new VKapi;
    vk->setClientId("4561989");
    vk->setRedirectUri("http://api.vkontakte.ru/blank.html");
    vk->setVersion(5.24);
    vk->setDisplay("mobile");
    std::string login = authWidget->leLogin->text().toStdString();
    std::string password = authWidget->lePassword->text().toStdString();
    vk->setLogin(login);
    vk->setPassword(password);
    std::string json = vk->parseVKHTML();
    if(!vk->getLastError().b)
    {
        musicList = new MusicList(this);
        connect(musicList->btnDownload, SIGNAL(clicked()), this, SLOT(Download()));
        std::cout<<"OK"<<std::endl;
        delete authWidget;
        vk->parseMusic(json);
        VKapi::Musics music = vk->getMusic();
        for(VKapi::Musics::iterator it = music.begin(); it != music.end(); it++)
        {
            QString MusicTitle = QString::fromStdString((*it).artist) + " - " + QString::fromStdString((*it).title);
            QListWidgetItem * item = new QListWidgetItem(MusicTitle, musicList->musicList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, QString::fromStdString((*it).url));
            musicList->musicList->addItem(item);
            // create list
            //std::string title = (*it).title;
            //std::string url = vk.parseMusicLink((*it).url);
            //std::cout<<"title: "<<title<< "  |  url: "<<url<<std::endl;
            //vk.DownloadFile(url, title+".mp3");
        }
        this->layout()->addWidget(musicList);
        //std::cout<<vk.getLastError().msg<<std::endl;
        //exit(0);
    }else{
        std::cout<<"OKASD"<<std::endl;
    }


    //delete authWidget;
}

void Window::Download()
{
    if(vk == NULL) return;
    musicList->btnDownload->setText("Download process...");

    for(int i = 0; i < musicList->musicList->count(); ++i)
    {
        QListWidgetItem* item = musicList->musicList->item(i);
        if(item->checkState() == Qt::Unchecked) continue;
        std::string url = item->data(Qt::UserRole).toString().toStdString();
        std::string filename = item->text().toStdString();
        std::cout<< url << " = " <<filename<<std::endl;
        vk->DownloadFile(url, filename+".mp3");
    }
    musicList->btnDownload->setText("Download");
    QMessageBox::warning(this, "OK", "Download is end");
}

void Window::ChooseSaveDirectory()
{
    QString dirname = QFileDialog::getExistingDirectory(this, "Select Save Directory", QDir::currentPath());
    std::cout<<dirname.toStdString()<<std::endl;

    std::string settingsFileName = "settings.json";
    std::string settingsFile = FileOperations::readFromFile(settingsFileName);
    Json::Value root;
    Json::Reader reader;

    bool bjsonparse = reader.parse(settingsFile, root);

    root["settings"]["save_path"] = dirname.toStdString();

    std::string path = root["settings"].get("save_path", "./").asString();

    std::string settings = Json::StyledWriter().write(root);

    FileOperations::writeToFile(settingsFileName, settings);
    vk->setSaveFileDirectory(path);
}

void Window::Exit()
{
    exit(0);
}















