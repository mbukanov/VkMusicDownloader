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
#include "vkapi.h"
#include <QMovie>

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
    VKapi *vk = NULL;
signals:

public slots:
    void Authorization();
    void Download();

    void OpenSettings();

    void ChooseSaveDirectory();
    void Exit();

};

#endif // WINDOW_H
