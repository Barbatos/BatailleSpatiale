#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

class NetworkClient
{

	public:
		void CloseSocket();
		NetworkClient(void);
		~NetworkClient(void);

		sf::SocketTCP socket;
};

#endif
