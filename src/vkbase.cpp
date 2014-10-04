#include "vkbase.h"


VKBase::VKBase()
{

}

VKBase::~VKBase()
{

}

void VKBase::Authorization()
{
    if(!_curl || getLogin().empty() || getPassword().empty())
        return;

    char errorBuffer[CURL_ERROR_SIZE];
    std::string buffer = "";	// for response
    std::string url = "https://login.vk.com/?act=login&soft=1&utf8=1";
    std::string request = "_origin=https://oauth.vk.com";
    //request += "&ip_h=62371f194b8af424e4";	// it need parse
    request += "&to=aHR0cHM6Ly9vYXV0aC52ay5jb20vYXV0aG9yaXplP2NsaWVudF9pZD00NTYxOTg5JnJlZGlyZWN0X3VyaT1odHRwJTNBJTJGJTJGYXBpLnZrb250YWt0ZS5ydSUyRmJsYW5rLmh0bWwmcmVzcG9uc2VfdHlwZT10b2tlbiZzY29wZT04JnY9NS4yNCZzdGF0ZT0mcmV2b2tlPTEmZGlzcGxheT1tb2JpbGU-"; // redirect url to base64
    request += "&email="+getLogin();
    request += "&pass="+getPassword();

    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, request.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &VKBase::writer);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, errorBuffer);
    CURLcode result = curl_easy_perform(_curl);
    curlCheckError(_curl, result, errorBuffer);

    _ip_h = parseIPhFromHeaders(buffer);
    _hash = parseHashFromHeaders(buffer);
}

std::string VKBase::parseHTML()
{
    std::string cookiestring = "";
    _curl = curl_easy_init();
    CURLcode result;
    std::string buffer = "";	// for response
    std::string url = "";	// for url

    char errorBuffer[CURL_ERROR_SIZE];
    if(!_curl)
    {
        printf("%s\n", "ERROR: curl_easy_init()");
        exit(0);
    }

    std::string scopes = "";
    std::vector<std::string> vscopes = getScopes();
    std::for_each(vscopes.begin(), vscopes.end(), [&scopes](std::string scope){
        scopes += scope+"&";
    });

    url = "https://oauth.vk.com/authorize?client_id=";
    url += getClientId();
    url += "&scope="+scopes+"redirect_uri=http://api.vkontakte.ru/blank.html&display=mobile&v=5.24&response_type=token&revoke=1";

    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(_curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(_curl, CURLOPT_COOKIEFILE, cookiestring.c_str());
    curl_easy_setopt(_curl, CURLOPT_PORT, 443);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, &VKBase::writer);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, errorBuffer);

    result = curl_easy_perform(_curl);
    curlCheckError(_curl, result, errorBuffer);


    buffer.clear();
    Authorization();

    // grant access
    url  = "https://login.vk.com/?act=grant_access&client_id="+getClientId();
    url += "&settings=8&redirect_uri=http%3A%2F%2Fapi.vkontakte.ru%2Fblank.html&response_type=token&direct_hash=85bc6b0b250f6f44d1&token_type=0&v=5.24";
    url += "&state=&display=mobile";
    url += "&ip_h="+_ip_h;
    url += "&hash="+_hash;
    url += "&https=1";

    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);
    result = curl_easy_perform(_curl);
    curlCheckError(_curl, result, errorBuffer);

    url = "https://api.vk.com/method/"+getMethod()+"?&access_token="+parseAccessTokenFromHeaders(buffer);
    buffer.clear();

    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_HEADER, 0);
    result = curl_easy_perform(_curl);
    curlCheckError(_curl, result, errorBuffer);

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

void VKBase::setClientId(std::string client_id)
{
    _client_id = client_id;
}

std::string VKBase::getClientId() const
{
    return _client_id;
}

VKBase::Errors VKBase::getLastError()
{
    return err;
}

std::string VKBase::parseIPhFromHeaders(std::string headers)
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

std::string VKBase::parseHashFromHeaders(std::string headers)
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

std::string VKBase::parseAccessTokenFromHeaders(std::string headers)
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


void VKBase::curlCheckError(CURL* curl, int result, char* errorBuffer)
{
    if(result != CURLE_OK)
    {
        std::cout<<"ERROR: "<<errorBuffer<<std::endl;
        curl_easy_cleanup(curl);
        exit(0);
    }
}

void VKBase::setLogin(std::string login)
{
    _login = login;
}

void VKBase::setPassword(std::string password)
{
    _password = password;
}

std::string VKBase::getLogin() const
{
    return _login;
}

std::string VKBase::getPassword() const
{
    return _password;
}

int VKBase::writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;
    if(buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

std::vector<std::string> VKBase::getScopes() const
{
    std::vector<std::string> v;
    return v;
}

std::string VKBase::getMethod() const
{
    return "";
}
