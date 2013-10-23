#ifndef _NETWORK_GLOBAL_H_
#define _NETWORK_GLOBAL_H_

// Inclusion des librairies permettant l'utilisation des sockets
// Les librairies sont différentes pour Windows et Linux
#ifdef _WIN32
	#include <winsock2.h> 
	#include <ws2tcpip.h>
	#include <iphlpapi.h>
	//#pragma comment(lib, "Ws2_32.lib") // Inclusion de la libraire winsock2
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <netdb.h>
	#include <arpa/inet.h> // pour utiliser inet_ntoa()
	#include <fcntl.h>
	#define closesocket(s) close(s) // la fonction closesocket() est pour windows, close() pour linux
	#define SOCKET int
#endif

#include <boost/lexical_cast.hpp>

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
		static int sendMessage(SOCKET curSocket, char * message, int messageSize);
		static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);
		static void getIP(char *ip);
		static void CloseSocket(SOCKET sock);
};


#endif
