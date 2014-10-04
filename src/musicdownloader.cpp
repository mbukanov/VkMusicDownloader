    #include "musicdownloader.h"

MusicDownloader::MusicDownloader(QObject *parent) :
    QObject(parent)
{
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
        downloader.Download(url, _path, filename, getReplace());
    }

    emit finished();
    return;
}


