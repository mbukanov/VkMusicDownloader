#include "vkapi.h"

VKapi::VKapi()
{

}

VKapi::~VKapi()
{

}

void VKapi::setScopes(const Scopes& scopes)
{
	_scopes = scopes;
}

Scopes VKapi::getScopes() const
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

void VKapi::setDisplay(const std::string& type)
{
	_type = type;
}

std::string VKapi::getDisplay() const
{
	return _display;
}
	
void VKapi::setVersion(const double v)
{
	_version = v;
}

double VKapi::getVersion() const
{
	return _version;
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

void VKapi::sendRequest(std::string& buff)
{
	// todo
}

std::string VKapi::recvRequest() const
{
	// todo
}