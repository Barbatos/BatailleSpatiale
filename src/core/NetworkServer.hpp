#ifndef _NETWORK_SERVER_H_
#define _NETWORK_SERVER_H_

class NetworkServer
{

	public:
		NetworkServer(void);
		~NetworkServer(void);
		void acceptNewClient(void);

		sf::TcpListener listener;

};

#endif

