#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>
#include <algorithm>
#include "OS.h"

class FileDownloader
{
public:
	FileDownloader();
	~FileDownloader();

	void setUrl(std::string url);
    virtual std::string getUrl() const;

	void setFilename(std::string filename);
    void setFullFilename(std::string filename);

    virtual std::string getFilename() const;
    virtual std::string getFullFilename() const;

    void setPath(std::string path);
    virtual std::string getPath() const;

    void setReplace(bool replace);
    bool getReplace() const;

    std::string EscapeSpecChars(std::string &str);

	static size_t DownloadedFileWriter(void *ptr, size_t size, size_t nmemb, FILE *stream);

	bool Download();
    bool Download(std::string &url, std::string &path, std::string &filename, bool replace);

protected:
    bool Request();
    void setParams();
	CURL* getCurl();

private:
	FILE* fp;
	CURL* curl;
	std::string _filename;
	std::string _url;
    std::string _path;
    std::string _fullfilename;
    bool _replace;

};

#endif
