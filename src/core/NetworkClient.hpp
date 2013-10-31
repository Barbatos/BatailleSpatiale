#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

class NetworkClient
{

	public:
		NetworkClient(string ip, unsigned short port);
		~NetworkClient(void);

		sf::TcpSocket socket;
};

#endif
