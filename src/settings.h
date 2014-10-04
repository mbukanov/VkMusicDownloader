#ifndef SETTINGS_H
#define SETTINGS_H

#include "jsoncpp/include/json/json.h"
#include "fileoperations.h"

class Settings
{
public:
    static Settings* init();

    Json::Value& getJson();
    Json::Value& setJson(std::string buffer);

    void save();

    static bool DeleteInstance();

protected:
    Settings();
    virtual ~Settings();
    static Settings* _self;
    Json::Value _root;
};

#endif // SETTINGS_H
