#include "musiclist.h"

MusicList::MusicList(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout);

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


