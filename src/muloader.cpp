#include "muloader.h"

MuLoader::MuLoader()
{
	setClientId("4561989");
	setRedirectUri("http://api.vkontakte.ru/blank.html");
	setDisplay("mobile");
	setVersion(5.24);
	setRevoke(false);
	Scopes scopes(1, "audio");
	setScopes(scopes);
}