#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "authwidget.h"
#include "musiclist.h"
#include <iostream>
#include <QMessageBox>
#include "vkapi.h"

class Window : public QDialog
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    AuthWidget * authWidget = NULL;
    MusicList * musicList = NULL;


private:
    VKapi *vk = NULL;
signals:

public slots:
    void Authorization();
    void Download();

};

#endif // WINDOW_H
