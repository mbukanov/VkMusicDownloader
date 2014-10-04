#include "vkmusic.h"

std::vector<VKMusic::Song> VKMusic::parseMusic()
{
    std::string html = parseHTML();

    Json::Value root;
    Json::Reader reader;

    reader.parse(html, root);

    for(Json::Value::iterator it = root["response"].begin(); it != root["response"].end(); it++)
    {
        Song s = { (*it)["artist"].asString(), (*it)["title"].asString(), (*it)["url"].asString() };
        _music.push_back(s);
    }

    return _music;
}

std::vector<VKMusic::Song> VKMusic::getMusic() const
{
    return _music;
}

std::string VKMusic::parseMusicLink(std::string link)
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
