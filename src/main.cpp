#include <iostream>
#include "vkapi.h"


int main(int argc, char** argv)
{
	VKapi vk;
	vk.setClientId("my_app_id");
	vk.setRedirectUri("http://api.vkontakte.ru/blank.html");
	vk.setVersion(5.24);
	vk.setDisplay("mobile");
	vk.setLogin("myemail");
	vk.setPassword("mypassword");
	std::string json = vk.parseVKHTML();
	std::cout<<json<<std::endl;
	return 0;
}