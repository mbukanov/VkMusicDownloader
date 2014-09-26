#include <vector>
#include <curl/curl.h>
#include <boost/regex.hpp>

class VKapi
{
public:
	typedef std::vector<std::string> Scopes;
	
	VKapi();
	virtual ~VKapi();

	virtual void setScopes(const Scopes& scopes);
	virtual Scopes getScopes() const;
	
	virtual void setRedirectUri(const std::string& ruri);
	virtual std::string getRedirectUri() const;
	
	virtual void setClientId(const std::string& client_id);
	virtual std::string getClientId() const;

	virtual void setDisplay(const std::string& type);
	virtual std::string getDisplay() const;
	
	virtual void setVersion(const double v);
	virtual double getVersionD() const;
	virtual std::string getVersionS() const;
	
	virtual void setRevoke(const bool rev);
	virtual bool getRevoke() const;
	
	virtual void setAccessToken(const std::string& access_token);
	virtual std::string getAccessTokenFromHeaders(std::string headers);
	virtual std::string getAccessToken() const;

	virtual std::string parseVKHTML();
	//virtual void setVKHTML(std::string html);

	void setLogin(const std::string& login);
	void setPassword(const std::string& password);
	std::string getLogin() const;
	std::string getPassword() const;

	static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);

	void curlCheckError(CURL* curl, int result, char* errorBuffer);


protected:
	virtual void sendRequest(std::string& buff);
	virtual std::string recvRequest() const;


private:
	std::string _login;
	std::string _password;

	std::string _client_id;
	bool _revoke;
	Scopes _scopes;
	std::string _type;
	std::string _access_token;
	double _version;
	std::string _ruri;
	std::string _display;
	CURL* curl;
};