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
	_filename = filename;
}

void FileDownloader::createFile()
{
	fp = fopen(getFilename().c_str(),"wb");
}

std::string FileDownloader::getUrl() const
{
	return _url;
}

std::string FileDownloader::getFilename() const
{
	return _filename;
}

CURL* FileDownloader::getCurl()
{
	return curl;
}

FILE* FileDownloader::getFile()
{
	return fp;
}

void FileDownloader::setParams()
{
	curl_easy_setopt(getCurl(), CURLOPT_URL, getUrl().c_str());
	curl_easy_setopt(getCurl(), CURLOPT_WRITEFUNCTION, &FileDownloader::DownloadedFileWriter);
	curl_easy_setopt(getCurl(), CURLOPT_WRITEDATA, getFile());
}

bool FileDownloader::Request()
{
	createFile();
	setParams();
	CURLcode res = curl_easy_perform(getCurl());
	if(res == CURLE_OK)
		return true;

	return false;
}

bool FileDownloader::Download()
{
	createFile();
	Request();
}

