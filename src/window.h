#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QFileDialog>
#include <QAction>
#include <QMenuBar>
#include "authwidget.h"
#include "musiclist.h"
#include <iostream>
#include <QMessageBox>
#include <jsoncpp/include/json/writer.h>
#include <fstream>
#include "settingswidget.h"
#include "vkmusic.h"
#include "musicdownloader.h"
#include <QThread>
#include <QTextEdit>
#include <QMovie>
#include <QApplication>

class Window : public QDialog
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    AuthWidget * authWidget = NULL;
    MusicList * musicList = NULL;
    SettingsWidget * settingsWidget = NULL;

    void createMenu();

private:
    VKMusic *vk;
    MusicDownloader * downloader;
    QThread *thread;

signals:

public slots:
    void Authorization();
    void Download();
    void DownloadEnd();

    void OpenSettings();

    void Exit();

};

#endif // WINDOW_H
