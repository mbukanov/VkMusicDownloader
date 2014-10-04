#include "FileDownloader.h"

FileDownloader::FileDownloader()
{
	curl = curl_easy_init();
}

FileDownloader::~FileDownloader()
{
	curl_easy_cleanup(curl);
	fclose(fp);
}

size_t FileDownloader::DownloadedFileWriter(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void FileDownloader::setUrl(std::string url)
{
	_url = url;
}

void FileDownloader::setFilename(std::string filename)
{
    _filename = EscapeSpecChars(filename);
    _fullfilename = getPath()+_filename;
}

void FileDownloader::setFullFilename(std::string filename)
{
    _fullfilename = EscapeSpecChars(filename);
}

std::string FileDownloader::getUrl() const
{
	return _url;
}

std::string FileDownloader::getFilename() const
{
	return _filename;
}

std::string FileDownloader::getFullFilename() const
{
    if(_fullfilename.empty())
        return getPath() + getFilename();

    return _fullfilename;
}

void FileDownloader::setPath(std::string path)
{
    _path = path;
    _fullfilename = path + getFilename();
}

std::string FileDownloader::getPath() const
{
    return _path;
}

void FileDownloader::setReplace(bool replace)
{
    _replace = replace;
}

bool FileDownloader::getReplace() const
{
    return _replace;
}

CURL* FileDownloader::getCurl()
{
	return curl;
}


void FileDownloader::setParams()
{
	curl_easy_setopt(getCurl(), CURLOPT_URL, getUrl().c_str());
	curl_easy_setopt(getCurl(), CURLOPT_WRITEFUNCTION, &FileDownloader::DownloadedFileWriter);
    curl_easy_setopt(getCurl(), CURLOPT_WRITEDATA, fp);
}

bool FileDownloader::Download()
{
    if(!getReplace() && file_exists(getFullFilename()))
        return false;

    return Request();
}

bool FileDownloader::Download(std::string &url, std::string &path, std::string &filename, bool replace)
{
    setUrl(url);
    setFilename( EscapeSpecChars(filename));
    setPath(path);
    setReplace(replace);
    std::cout<<"FullFilename: "<<getFullFilename()<<std::endl;
    if(!getReplace() && file_exists(getFullFilename()))
        return false;

    return Request();
}

std::string FileDownloader::EscapeSpecChars(std::string &str)
{
    std::string result;
    std::list<char> specChars = {
        '\'',
        '"',
        '/',
        '(',
        ')'
    };

    std::string::iterator it;
    for(it = str.begin(); it != str.end(); it++)
    {
        std::list<char>::iterator p = std::find(specChars.begin(), specChars.end(), *it);
        /*
        if( p != specChars.end() )
            result += "\\";
        result += *it;
        */
        if( p != specChars.end())
            result += "_";
        else
            result += *it;
    }
    return result;
}


bool FileDownloader::Request()
{
    // Create File
    fp = fopen(getFullFilename().c_str(),"wb");

    // Set Curl Params
    setParams();

    // Execute
    CURLcode res = curl_easy_perform(getCurl());
    if(res == CURLE_OK)
    {
        fclose(fp);
        return true;
    }

    fclose(fp);
    return false;
}

