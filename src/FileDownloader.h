#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <stdio.h>

class FileDownloader
{
public:
	FileDownloader();
	~FileDownloader();

	void setUrl(std::string url);
	std::string getUrl() const;

	void setFilename(std::string filename);
	std::string getFilename() const;

	static size_t DownloadedFileWriter(void *ptr, size_t size, size_t nmemb, FILE *stream);

	void setParams();
	FILE* getFile();
	bool Request();

	bool Download();

protected:
	void createFile();

	CURL* getCurl();

private:
	FILE* fp;
	CURL* curl;
	std::string _filename;
	std::string _url;

};

#endif
