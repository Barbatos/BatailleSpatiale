#ifndef _NETWORK_H_
#define _NETWORK_H_

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
	#include <netdb.h>
	#include <arpa/inet.h> // pour utiliser inet_ntoa()
	#define closesocket(s) close(s) // la fonction closesocket() est pour windows, close() pour linux
#endif

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

class Network {

	public:
		void InitSocket();
		void FermerSocket();
		void EnvoyerPaquet(char *to, char *donnees, int longueur);
		void RecevoirPaquet(char *from, char *donnees);
		void getIP(char *ip);
		void ParserRequete(char *from, char *requete);
		static Network& Instance() {
	        static Network singleton;
	        return singleton;
	    }

	protected:
		#ifdef _WIN32
			WSADATA donneesInit;	
			SOCKET sock;			
		#else
			int sock;				// Numéro de la socket
		#endif
		sockaddr_in adresse; // Paramètres de la connexion

};

#endif // _NETWORK_H_
