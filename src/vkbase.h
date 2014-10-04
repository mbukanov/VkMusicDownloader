#ifndef VKBASE_H
#define VKBASE_H



#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/regex.hpp>
#include "jsoncpp/include/json/json.h"

class VKBase
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

    VKBase();
    virtual ~VKBase();

    void Authorization();
    std::string parseHTML();
    void setScopes(std::vector<std::string> Scopes);
    virtual std::vector<std::string> getScopes() const;
    virtual std::string getMethod() const;

    void setLogin(std::string login);
    void setPassword(std::string password);

    std::string getLogin() const;
    std::string getPassword() const;

    void setClientId(std::string client_id);
    std::string getClientId() const;

    Errors getLastError();

    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);


protected:
    CURL* _curl;
    std::string _login;
    std::string _password;
    std::vector<std::string> _scopes;

    std::string parseAccessTokenFromHeaders(std::string buffer);
    std::string parseIPhFromHeaders(std::string buffer);
    std::string parseHashFromHeaders(std::string buffer);
    void curlCheckError(CURL* curl, int result, char* errorBuffer);

    std::vector<Song> _tracks;

    std::string _client_id;
    std::string _ip_h;
    std::string _hash;

    Errors err;
};

#endif // VKBASE_H
