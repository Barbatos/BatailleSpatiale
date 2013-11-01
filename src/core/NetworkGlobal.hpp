#ifndef _NETWORK_GLOBAL_H_
#define _NETWORK_GLOBAL_H_

#include "../global.hpp"

class NetworkGlobal
{

	public:
		static void sendMessage(sf::TcpSocket& socket, sf::Packet& packet);
		static bool getMessage(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout);
};


#endif
