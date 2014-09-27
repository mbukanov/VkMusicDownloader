#include <iostream>
#include "vkapi.h"


int main(int argc, char** argv)
{
	VKapi vk;
	vk.setClientId("4561989");
	vk.setRedirectUri("http://api.vkontakte.ru/blank.html");
	vk.setVersion(5.24);
	vk.setDisplay("mobile");
	vk.setLogin("myemail");
	vk.setPassword("mypassword");
	std::string json = vk.parseVKHTML();
	if(vk.getLastError().b)
	{
		std::cout<<vk.getLastError().msg<<std::endl;
		exit(0);
	}

	vk.parseMusic(json);
	VKapi::Musics music = vk.getMusic();
	for(VKapi::Musics::iterator it = music.begin(); it != music.end(); it++)
	{
		std::string title = (*it).title;
		std::string url = vk.parseMusicLink((*it).url);
		std::cout<<"title: "<<title<< "  |  url: "<<url<<std::endl;
		vk.DownloadFile(url, title+".mp3");
	}

	return 0;
}
