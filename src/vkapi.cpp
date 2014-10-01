#include "vkapi.h"

VKapi::VKapi()
{
	err.b = false;
	err.msg = "";
    std::string temp_settingsFile = "settings.json";
    std::string settingsFile = FileOperations::readFromFile(temp_settingsFile);
    Json::Value root;
    Json::Reader reader;

    bool bjsonparse = reader.parse(settingsFile, root);
    std::string path = root["settings"].get("save_path", "./").asString();
    setSaveFileDirectory(path);
}

VKapi::~VKapi()
{
    //delete curl;
}

void VKapi::setScopes(const Scopes& scopes)
{
	_scopes = scopes;
}

VKapi::Scopes VKapi::getScopes() const
{
	return _scopes;
}

void VKapi::setRedirectUri(const std::string& ruri)
{
	_ruri = ruri;
}

std::string VKapi::getRedirectUri() const
{
	return _ruri;
}


void VKapi::setClientId(const std::string& client_id)
{
	_client_id = client_id;
}

std::string VKapi::getClientId() const
{
	return _client_id;
}

void VKapi::setDisplay(const std::string& display)
{
	_display = display;
}

std::string VKapi::getDisplay() const
{
	return _display;
}
	
void VKapi::setVersion(const double v)
{
	_version = v;
}

double VKapi::getVersionD() const
{
	return _version;
}

std::string VKapi::getVersionS() const
{
	std::ostringstream strs;
	strs << _version;
	return strs.str();
}
	
void VKapi::setRevoke(const bool rev)
{
	_revoke = rev;
}

bool VKapi::getRevoke() const
{
	return _revoke;
}
	
void VKapi::setAccessToken(const std::string& access_token)
{
	_access_token = access_token;
}

std::string VKapi::getAccessToken() const
{
	return _access_token;
}

std::string VKapi::getAccessTokenFromHeaders(std::string headers)
{
	boost::smatch smatch_data;

    std::string::const_iterator iStart = headers.begin();
    std::string::const_iterator iEnd = headers.end();

    boost::regex regex_at("access_token=((\\d|\\w)+)");

    std::string result;

    while(boost::regex_search(iStart, iEnd, smatch_data, regex_at))
    {
        result = smatch_data[1];
        iStart = smatch_data[0].second;
    }
    return result;
}

std::string VKapi::getIPhFromHeaders(std::string headers)
{
    boost::smatch smatch_data;

    std::string::const_iterator iStart = headers.begin();
    std::string::const_iterator iEnd = headers.end();

    boost::regex regex_at("<form.+(ip_h=(\\w+|\\d+)&hash=(\\w+|\\d+)).+>");

    std::string result;

    while(boost::regex_search(iStart, iEnd, smatch_data, regex_at))
    {
        result = smatch_data[2];
        iStart = smatch_data[0].second;
    }
    return result;
}

std::string VKapi::getHashFromHeaders(std::string headers)
{
    boost::smatch smatch_data;

    std::string::const_iterator iStart = headers.begin();
    std::string::const_iterator iEnd = headers.end();

    boost::regex regex_at("<form.+(ip_h=(\\w+|\\d+)&hash=(\\w+|\\d+)).+>");

    std::string result;

    while(boost::regex_search(iStart, iEnd, smatch_data, regex_at))
    {
        result = smatch_data[3];
        iStart = smatch_data[0].second;
    }
    return result;
}

void VKapi::sendRequest(std::string& buff)
{
	// todo
}

std::string VKapi::recvRequest() const
{
	// todo
}

int VKapi::writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
	int result = 0;
	if(buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}

size_t VKapi::DownloadedFileWriter(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

/*
	Authorization()

	Send request with Login and Password to authorization page
	Request is page with HTML: Grant access if auth success, login page if auth failure
*/
void VKapi::Authorization()
{
	if(!curl)
		return;

	char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer = "";	// for response
	std::string url = "https://login.vk.com/?act=login&soft=1&utf8=1"; 
	std::string request = "_origin=https://oauth.vk.com";
    //request += "&ip_h=62371f194b8af424e4";	// it need parse
    request += "&to=aHR0cHM6Ly9vYXV0aC52ay5jb20vYXV0aG9yaXplP2NsaWVudF9pZD00NTYxOTg5JnJlZGlyZWN0X3VyaT1odHRwJTNBJTJGJTJGYXBpLnZrb250YWt0ZS5ydSUyRmJsYW5rLmh0bWwmcmVzcG9uc2VfdHlwZT10b2tlbiZzY29wZT04JnY9NS4yNCZzdGF0ZT0mcmV2b2tlPTEmZGlzcGxheT1tb2JpbGU-"; // redirect url to base64
    request += "&email="+getLogin();
    request += "&pass="+getPassword();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &VKapi::writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
    CURLcode result = curl_easy_perform(curl);
	curlCheckError(curl, result, errorBuffer); 

    _ip_h = getIPhFromHeaders(buffer);
    _hash = getHashFromHeaders(buffer);
}


/*
	parseVKHTML

	1. Parse main page, but you need authorizate(Reload on the Login page)
	2. Authorization
	3. Grant Access
	4. Recv response with json of your Music
*/
std::string VKapi::parseVKHTML()
{
	std::string cookiestring = "";
	curl = curl_easy_init();
	CURLcode result;
	std::string buffer = "";	// for response
	std::string url = "";	// for url

	char errorBuffer[CURL_ERROR_SIZE];
	if(!curl)
	{
		printf("%s\n", "ERROR: curl_easy_init()");
		exit(0);
	}

	url = "https://oauth.vk.com/authorize?client_id=";
	url += getClientId();
	url += "&scope=audio&redirect_uri=http://api.vkontakte.ru/blank.html&display=mobile&v=5.24&response_type=token&revoke=1";

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiestring.c_str());
	curl_easy_setopt(curl, CURLOPT_PORT, 443);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &VKapi::writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);

	result = curl_easy_perform(curl);
	curlCheckError(curl, result, errorBuffer);


	buffer.clear();
	Authorization();
 
	// grant access
	url  = "https://login.vk.com/?act=grant_access&client_id="+getClientId();
    url += "&settings=8&redirect_uri=http%3A%2F%2Fapi.vkontakte.ru%2Fblank.html&response_type=token&direct_hash=85bc6b0b250f6f44d1&token_type=0&v="+getVersionS();
	url += "&state=&display="+getDisplay();
    url += "&ip_h="+_ip_h;
    url += "&hash="+_hash;
    url += "&https=1";

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	result = curl_easy_perform(curl);
	curlCheckError(curl, result, errorBuffer);

	url = "https://api.vk.com/method/audio.get?&access_token="+getAccessTokenFromHeaders(buffer);
	buffer.clear();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	result = curl_easy_perform(curl);
	curlCheckError(curl, result, errorBuffer);

	Json::Value root;
	Json::Reader reader;

	bool bjsonparse = reader.parse(buffer, root);
	if(bjsonparse && root["error"].get("error_code", 0).asInt())
	{
		err.b = true;
		err.msg = root["error"].get("error_msg", "false").asString();
    }else{
        err.b = false;
        err.msg = "";
    }

	return buffer;
}


void VKapi::setLogin(const std::string& login)
{
	_login = login;
}

void VKapi::setPassword(const std::string& password)
{
	_password = password;
}

std::string VKapi::getLogin() const
{
	return _login;
}

std::string VKapi::getPassword() const
{
    return _password;
}

std::string VKapi::EscapeSpecChars(std::string &str)
{
    std::string result;
    std::list<char> specChars = {
        '\'',
        '"',
        '/'
    };

    std::string::iterator it;
    for(it = str.begin(); it != str.end(); it++)
    {
        std::list<char>::iterator p = std::find(specChars.begin(), specChars.end(), *it);
        if( p != specChars.end() )
            result += "\\";
        result += *it;
    }
    return result;
}

void VKapi::curlCheckError(CURL* curl, int result, char* errorBuffer)
{
	if(result != CURLE_OK)
	{
		std::cout<<"ERROR: "<<errorBuffer<<std::endl;
		curl_easy_cleanup(curl);
		exit(0);
	}
}

void VKapi::parseMusic(std::string json)
{
	Json::Value root;
	Json::Reader reader;

	bool parsingSucceful = reader.parse(json, root);

	for(Json::Value::iterator it = root["response"].begin(); it != root["response"].end(); it++)
	{
		Song s = { (*it)["artist"].asString(), (*it)["title"].asString(), (*it)["url"].asString() };
		_jsonMusic.push_back(s);
	}
}

VKapi::Musics VKapi::getMusic() const
{
	return _jsonMusic;
}

std::string VKapi::parseMusicLink(std::string link)
{
	// src: https://qwerty.mp3?qwerty
	// dst: https://qwerty.mp3
	std::string result = "";
	std::string::iterator iStart = link.begin();
	std::string::iterator iEnd = link.end();
	for(std::string::iterator it = iStart; it != iEnd; it++)
	{
		if( (*it) == '?' ) break;
		result += (*it);
	}
	return result;
}

bool VKapi::DownloadFile(std::string url, std::string filename)
{
	downloader.setUrl(url);
    filename = EscapeSpecChars(filename);
    filename = getSaveFileDirectory() + filename; // firectory + filename;
	downloader.setFilename(filename);
	return downloader.Download();
}

VKapi::Errors VKapi::getLastError()
{
    return err;
}

std::string VKapi::getSaveFileDirectory() const
{
    return _saveFileDirectory;
}

void VKapi::setSaveFileDirectory(std::string directory)
{

    std::string::iterator it = directory.end() - 1;
    if(*it != '/') // for *nix
    {
        directory += "/";
    };
    std::cout << directory <<std::endl;
    _saveFileDirectory = directory;
}
