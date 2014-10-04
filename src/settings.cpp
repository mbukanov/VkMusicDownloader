#include "settings.h"

Settings* Settings::init()
{
    if(!_self)
    {
        _self = new Settings();
        Json::Reader reader;
        std::string filename = "settings.json";
        std::string buffer = FileOperations::readFromFile(filename);
        reader.parse(buffer, _self->_root);
    }
    return _self;
}

Json::Value& Settings::getJson()
{
    return _self->_root;
}

Json::Value& Settings::setJson(std::string buffer)
{
    Json::Reader reader;
    reader.parse(buffer, _self->_root);
    return _self->_root;
}

void Settings::save()
{
    std::string buffer = Json::StyledWriter().write(_self->_root);
    std::string filename = "settings.json";
    FileOperations::writeToFile(filename, buffer);

}

bool Settings::DeleteInstance()
{
    if(_self)
    {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}

Settings::Settings(){}

Settings::~Settings(){}

Settings* Settings::_self = NULL;
