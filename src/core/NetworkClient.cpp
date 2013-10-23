#include "../global.hpp"

NetworkClient::NetworkClient(void){
	int port = 1337;
	int flags;
	char ip[32];
	#ifdef _WIN32
	WSADATA wsaData;
	unsigned long cmd = 1;
	#endif

	ConnectSocket = -1;

	// Initialisation de la lib Winsock (pour Windows seulement)
	#ifdef _WIN32
	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		cerr << "[NETWORK] L'initialisation de Winsock a echoue avec l'erreur: " << WSAGetLastError() << endl;
		return;
	} 
	else {
		cout << "[NETWORK] Initialisation de Winsock reussie." << endl;
	}
	#endif

	if( (ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
		cerr << "[NETWORK] L'initialisation de la socket TCP a echoue." << endl;
		return;
	}
	else {
		cout << "[NETWORK] Initialisation de la socket TCP reussie." << endl;
	}

	memset(&adresse, 0, sizeof(adresse));

	adresse.sin_family = AF_INET;

	// On écoute sur toutes les IPs locales
	adresse.sin_addr.s_addr = htonl(INADDR_ANY);

	// Définition du port
	adresse.sin_port = htons(port); 

	if (connect(ConnectSocket, (struct sockaddr *)&adresse, sizeof(adresse)) < 0){
		cerr << "[NETWORK] Impossible de se connecter au serveur" << endl;
		NetworkGlobal::CloseSocket(ConnectSocket);
		return;
	}

	// On met la socket en mode "non bloquant"
#ifdef _WIN32
	ioctlsocket(ConnectSocket, FIONBIO, &cmd);
#else
	flags = fcntl(ConnectSocket, F_GETFL, 0);
	fcntl(ConnectSocket, F_SETFL, flags | O_NONBLOCK);
#endif	

	NetworkGlobal::getIP(ip);

	cout << "[NETWORK] ip: " << ip << endl;
	cout << "[NETWORK] port: " << port << endl;
}
