#ifndef _RESEAU_GLOBAL_H_
#define _RESEAU_GLOBAL_H_

#include "../global.hpp"

class ReseauGlobal
{

	public:
		static bool ReceptionMessage(sf::TcpSocket& socket, sf::Packet& paquet, sf::Time timeout = sf::seconds(0.0f));
		static void EnvoiMessage(sf::TcpSocket& socket, sf::Packet& paquet);
};

#endif
