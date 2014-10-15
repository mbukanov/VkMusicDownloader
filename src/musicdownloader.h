#ifndef MUSICDOWNLOADER_H
#define MUSICDOWNLOADER_H

#include <QObject>
#include <QLabel>
#include "FileDownloader.h"
#include "vkbase.h"
#include <string>

class MusicDownloader : public QObject
{
    Q_OBJECT
public:
    explicit MusicDownloader(QObject *parent = 0);
    void setMusicList(std::vector<std::pair<std::string, std::string> > &tracks);
    void setPath(std::string path);
    void setReplace(bool replace);

    void setOutputTrackLabel(QLabel *w);

    std::string getPath() const;
    bool getReplace() const;

private:
    FileDownloader downloader;
    std::vector<std::pair<std::string, std::string> > _tracks;
    std::string _path;
    bool _replace;
    QLabel* lblOutput;

signals:

public slots:
    void process();
    //void stop();

signals:
    void finished();

};

#endif // MUSICDOWNLOADER_H
