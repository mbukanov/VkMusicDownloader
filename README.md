VkMusicDownloader
==================

My simple vk.com music downloader


TODO: 
-----
simple vk.api:
1. Auth: 
https://oauth.vk.com/authorize?client_id=<client_id>&scope=audio&redirect_uri=http://api.vkontakte.ru/blank.html&display=mobile&v=5.24&response_type=token&revoke=1

Response: auth_token

2. Get music:
https://api.vk.com/method/audio.get?&access_token=<auth_token>

Response my music files in JSON view with:
"artist"	: <artist>,
"title"		: <title>,
"url" 		: <http://qwerty.vk.me/uqwerty/audios/qwerty.mp3>

3. Parse JSON
4. Download select url


