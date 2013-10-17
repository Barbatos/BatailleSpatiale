#include "../global.hpp"

int NetworkGlobal::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
    return send(curSocket, message, messageSize, 0);
}

int NetworkGlobal::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
    return recv(curSocket, buffer, bufSize, 0);
}

void NetworkGlobal::getIP(char *ip){
	char hostname[256];
	struct hostent *hostInfo;
	struct in_addr **addr_list;

	if ( gethostname( hostname, 256 ) == -1 ) {
		return;
	}

	// on récupère les informations du host
	if (!(hostInfo = gethostbyname( hostname ))) {
		return;
	}

	addr_list = (struct in_addr **)hostInfo->h_addr_list;

	strcpy(ip, inet_ntoa(*addr_list[0]));
}

// Fermeture d'une socket
void NetworkGlobal::CloseSocket(SOCKET sock){

	// On ferme la socket
	closesocket(sock);

	// On quitte Winsock (windows seulement)
#ifdef _WIN32
	WSACleanup();
#endif

	cout << "[NETWORK] Fermeture de la socket reussie !" << endl;

	return;
}
