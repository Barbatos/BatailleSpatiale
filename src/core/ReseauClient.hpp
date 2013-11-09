#ifndef _RESEAU_CLIENT_H_
#define _RESEAU_CLIENT_H_

#include "../global.hpp"

class ReseauClient
{

	public:
		ReseauClient(string ip, unsigned short port);
		~ReseauClient(void);
		
		void TraiterPaquetServeur(sf::Packet& paquet);

		sf::TcpSocket socket;
};

#endif
