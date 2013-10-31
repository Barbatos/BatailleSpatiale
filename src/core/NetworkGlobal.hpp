#ifndef _NETWORK_GLOBAL_H_
#define _NETWORK_GLOBAL_H_

#include "../global.hpp"
#include <SFML/Network.hpp>

// Longueur maximale d'un paquet reçu par le serveur
#define MAX_LONGUEUR_PAQUET 1515

typedef enum {
	STC_CTS_NOTHING = 0,

	// client to server
	CTS_CONNEXION = 1,
	CTS_DECONNEXION = 2,

	// server to client
	STC_CONNEXION = 1000,
	STC_DECONNEXION = 1001,
} requete_s;

enum PacketTypes {
	INIT_CONNECTION = 0,
	ACTION_EVENT = 1,
}; 

struct Packet {
	unsigned int packet_type;

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

class NetworkGlobal
{

	public:
		static void sendMessage(sf::TcpSocket socket, char *message);
		static void getMessage(sf::TcpSocket socket);
};


#endif
