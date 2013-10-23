#include "../global.hpp"

NetworkServer::NetworkServer(void){
	int port = 1337;
	int flags;
	char ip[32];
	#ifdef _WIN32
	WSADATA wsaData;
	unsigned long cmd = 1;
	#endif
	ListenSocket = -1;
	ClientSocket = -1;

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

	if( (ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
		cerr << "[NETWORK] L'initialisation de la socket TCP a echoue." << endl;
		return;
	}
	else {
		cout << "[NETWORK] Initialisation de la socket TCP reussie." << endl;
	}

	// On met la socket en mode "non bloquant"
#ifdef _WIN32
	ioctlsocket(ListenSocket, FIONBIO, &cmd);
#else
	flags = fcntl(ListenSocket, F_GETFL, 0);
	fcntl(ListenSocket, F_SETFL, flags | O_NONBLOCK);
#endif


	memset(&adresse, 0, sizeof(adresse));

	adresse.sin_family = AF_INET;

	// On écoute sur toutes les IPs locales
	adresse.sin_addr.s_addr = htonl(INADDR_ANY);

	// Définition du port
	adresse.sin_port = htons(port); 

	// On attribue les infos à la socket
	if( bind(ListenSocket, (struct sockaddr*)&adresse, sizeof(adresse)) == -1 ){
		cerr << "[NETWORK] Impossible d'ouvrir la socket sur le port " << port << endl;
		NetworkGlobal::CloseSocket(ListenSocket);
		return;
	}

	if(listen(ListenSocket, 10) < 0){
		cerr << "[NETWORK] Impossible d'ecouter les connexions entrantes" << endl;
		NetworkGlobal::CloseSocket(ListenSocket);
		return;
	}

	NetworkGlobal::getIP(ip);

	cout << "[NETWORK] ip: " << ip << endl;
	cout << "[NETWORK] port: " << port << endl;
}

bool NetworkServer::acceptNewClient(unsigned int & id)
{
	ClientSocket = accept(ListenSocket, NULL, NULL);

	if (ClientSocket != -1) 
	{
		char value = 1;
		setsockopt( ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );

		cout << "yay!" << endl;

		//sessions.insert( pair<unsigned int, SOCKET>(id, ClientSocket) );

		return true;
	}

	return false;
}

int NetworkServer::receiveData(unsigned int client_id, char *recvbuf)
{
	int i;

	if( sessions.find(client_id) != sessions.end() )
	{
		SOCKET currentSocket = sessions[client_id];
		if( (i = NetworkGlobal::receiveMessage(currentSocket, recvbuf, MAX_LONGUEUR_PAQUET)) == 0) {
			cout << "Connection closed" << endl;
			NetworkGlobal::CloseSocket(currentSocket);
		}
		return i;
	}
	return 0;
} 

/*void NetworkServer::receiveFromClients()
{
	Packet packet;

	std::map<unsigned int, SOCKET>::iterator iter;

	for(iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0) {
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length) 
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(Packet);

			switch (packet.packet_type) {

				case INIT_CONNECTION:

					printf("server received init packet from client\n");

					break;

				case ACTION_EVENT:

					printf("server received action event packet from client\n");

					break;

				default:

					printf("error in packet types\n");

					break;
			}
		}
	}
}
*/
