#ifndef VKMUSIC_H
#define VKMUSIC_H

#include "vkbase.h"
#include <vector>

class VKMusic : public VKBase
{
public:
    struct Song
    {
        std::string artist;
        std::string title;
        std::string url;
    };

    virtual ~VKMusic(){}

    std::vector<Song> parseMusic();
    std::vector<Song> getMusic() const;

    std::string parseMusicLink(std::string link);

    virtual std::vector<std::string> getScopes() const
    {
        std::vector<std::string> scopes(1, "audio");
        return scopes;
    }

    virtual std::string getMethod() const
    {
        return "audio.get";
    }

protected:

    std::vector<Song> _music;


};
#endif // VKMUSIC_H
