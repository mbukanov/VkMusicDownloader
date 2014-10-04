#include "musiclist.h"

MusicList::MusicList(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout);

    QHBoxLayout * layLoader = new QHBoxLayout();
    loaderLabel = new QLabel("", this);
    movieLabel = new QLabel(this);
    loaderMovie = new QMovie("loader.gif");
    movieLabel->setMovie(loaderMovie);
    layLoader->addWidget(loaderLabel);
    layLoader->addWidget(movieLabel);
    this->layout()->addItem(layLoader);


    btnCheckAll = new QPushButton("Check All", this);
    btnUncheckAll = new QPushButton("Uncheck All", this);

    QHBoxLayout * layChecks = new QHBoxLayout(this);
    layChecks->addWidget(btnCheckAll);
    layChecks->addWidget(btnUncheckAll);

    btnDownload = new QPushButton("Download", this);
    musicList = new QListWidget(this);

    this->layout()->addItem(layChecks);
    this->layout()->addWidget(musicList);
    this->layout()->addWidget(btnDownload);

    QObject::connect(btnCheckAll, SIGNAL(clicked()), this, SLOT(CheckAll()));
    QObject::connect(btnUncheckAll, SIGNAL(clicked()), this, SLOT(UncheckAll()));
}

void MusicList::StartLoadAnim()
{
    loaderLabel->setText("Downloading...");
    movieLabel->show();
    loaderMovie->start();
    btnDownload->setEnabled(false);
}

void MusicList::StopLoadAnim()
{
    loaderLabel->setText("");
    loaderMovie->stop();
    movieLabel->hide();
    btnDownload->setEnabled(true);
}

void MusicList::CheckAll()
{
    for(int i = 0; i < musicList->count(); ++i)
    {
        musicList->item(i)->setCheckState(Qt::Checked);
    }
}

void MusicList::UncheckAll()
{
    for(int i = 0; i < musicList->count(); ++i)
    {
        musicList->item(i)->setCheckState(Qt::Unchecked);
    }
}


