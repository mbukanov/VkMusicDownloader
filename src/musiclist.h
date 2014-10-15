#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QMovie>

class MusicList : public QWidget
{
    Q_OBJECT
public:
    explicit MusicList(QWidget *parent = 0);
    friend class Window;

    QLabel *loaderLabel;
    QMovie *loaderMovie;
    QLabel *movieLabel;

    QLabel * lblDownloadMusicTitle;

    QListWidget * musicList;
    QPushButton * btnDownload;
    QPushButton * btnCheckAll;
    QPushButton * btnUncheckAll;

    void StartLoadAnim();
    void StopLoadAnim();

signals:

public slots:
    void CheckAll();
    void UncheckAll();

};

#endif // MUSICLIST_H
