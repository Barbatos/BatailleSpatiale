#ifndef _NETWORK_SERVER_H_
#define _NETWORK_SERVER_H_

class NetworkServer
{

	public:
		NetworkServer(unsigned short port);
		~NetworkServer(void);
		void acceptNewClient(void);

		sf::TcpListener listener;
		sf::SocketSelector selector;

		list<sf::TcpSocket*> clients;

};

#endif

