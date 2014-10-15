    #include "musicdownloader.h"

MusicDownloader::MusicDownloader(QObject *parent) :
    QObject(parent)
{
    lblOutput = NULL;
}

void MusicDownloader::setMusicList(std::vector<std::pair<std::string, std::string> > &tracks)
{
    _tracks = tracks;
}

void MusicDownloader::setPath(std::string path)
{
    _path = path;
}

void MusicDownloader::setReplace(bool replace)
{
    _replace = replace;
}

void MusicDownloader::setOutputTrackLabel(QLabel *w)
{
    lblOutput = w;
}

std::string MusicDownloader::getPath() const
{
    return _path;
}

bool MusicDownloader::getReplace() const
{
    return _replace;
}

void MusicDownloader::process()
{
    for(int i = 0; i < _tracks.size(); i++)
    {
        std::string url = _tracks[i].first;
        std::string filename = _tracks[i].second;

        if(lblOutput != NULL)
            lblOutput->setText(QString::fromStdString(filename));

        downloader.Download(url, _path, filename, getReplace());
    }

    emit finished();
    return;
}


