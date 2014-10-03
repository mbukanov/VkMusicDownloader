#ifndef VKAPI_H
#define VKAPI_H

#include <vector>
#include "jsoncpp/include/json/json.h" // -ljsoncpp -L. (include libjsoncpp.a)
#include <curl/curl.h>
#include <boost/regex.hpp>
#include <algorithm>
#include <list>
#include "OS.h"
#include "fileoperations.h"
#include "FileDownloader.h"

class VKapi
{
public:

	struct Errors
	{
		bool b;
		std::string msg;
	};

	struct Song
	{
		std::string artist;
		std::string title;
		std::string url;

	};

	typedef std::vector<std::string> Scopes;
	typedef std::vector<Song> Musics;
	
	VKapi();
	~VKapi();

	void setScopes(const Scopes& scopes);
	Scopes getScopes() const;
	
	void setRedirectUri(const std::string& ruri);
	std::string getRedirectUri() const;
	
	void setClientId(const std::string& client_id);
	std::string getClientId() const;

	void setDisplay(const std::string& type);
	std::string getDisplay() const;

	void Authorization();
	
	void setVersion(const double v);
	double getVersionD() const;
	std::string getVersionS() const;
	
	void setRevoke(const bool rev);
	bool getRevoke() const;
	
	void setAccessToken(const std::string& access_token);
    std::string getAccessTokenFromHeaders(std::string headers);
    std::string getIPhFromHeaders(std::string headers);
    std::string getHashFromHeaders(std::string headers);

	std::string getAccessToken() const;

	std::string parseVKHTML();

	void parseMusic(std::string json);

	std::string parseMusicLink(std::string link);

	Musics getMusic() const;

	bool DownloadFile(std::string url, std::string filename);

	void setLogin(const std::string& login);
	void setPassword(const std::string& password);
	std::string getLogin() const;
	std::string getPassword() const;

    std::string EscapeSpecChars(std::string &str);

	Errors getLastError();

    void setSaveFileDirectory(std::string directory);
    std::string getSaveFileDirectory() const;

	static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);
	static size_t DownloadedFileWriter(void *ptr, size_t size, size_t nmemb, FILE *stream);

    bool ReplaceFiles() const { return _replaceExistingMusicFiles; }
    void setReplaceFiles(bool replace);

	void curlCheckError(CURL* curl, int result, char* errorBuffer);

    void setFilesInDirectory();


private:
	FileDownloader downloader;

	std::string _login;
	std::string _password;

	std::string _client_id;
	bool _revoke;
	Scopes _scopes;
	std::string _type;
	std::string _access_token;
    std::string _ip_h;
    std::string _hash;
	double _version;
	std::string _ruri;
	std::string _display;
	CURL* curl;
    std::string _saveFileDirectory;
    bool _replaceExistingMusicFiles;
	Errors err;

    std::set<std::string> _filesInDirectory; // for (not) replace downloaded files

	Musics _jsonMusic;

};

#endif
