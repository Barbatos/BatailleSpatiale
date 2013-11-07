#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

#include "../global.hpp"

class NetworkClient
{

	public:
		NetworkClient(string ip, unsigned short port);
		~NetworkClient(void);
		
		void ParseServerPacket(sf::Packet& packet);

		sf::TcpSocket socket;
};

#endif
