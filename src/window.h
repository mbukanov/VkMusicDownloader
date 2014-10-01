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
#include "vkapi.h"

class Window : public QDialog
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    AuthWidget * authWidget = NULL;
    MusicList * musicList = NULL;

    void createMenu();

private:
    VKapi *vk = NULL;
signals:

public slots:
    void Authorization();
    void Download();

    void ChooseSaveDirectory();
    void Exit();

};

#endif // WINDOW_H
