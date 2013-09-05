#include "../global.hpp"


// Initialisation de la socket
void Network::InitSocket(){
	int port = 1337; // @TODO: remplacer ça par une cvar
	char ip[32];

	// Initialisation de la lib Winsock (pour Windows seulement)
#ifdef _WIN32
	if( WSAStartup(MAKEWORD(2,2), &donneesInit) != 0) {
		cerr << "[NETWORK] L'initialisation de Winsock a echoue avec l'erreur: " << WSAGetLastError() << endl;
		return;
	} 
	else {
		cout << "[NETWORK] Initialisation de Winsock reussie." << endl;
	}
#endif

	// On essaye de créer la socket (UDP)
	if ((sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		cerr << "[NETWORK] L'initialisation de la socket UDP a echoue." << endl;
		return;
	} 
	else {
		cout << "[NETWORK] Initialisation de la socket UDP reussie." << endl;
	}

	adresse.sin_family = AF_INET;

	// On écoute sur toutes les IPs locales
	adresse.sin_addr.s_addr = htonl(INADDR_ANY);

	// Définition du port
	adresse.sin_port = htons(port); 

	#ifdef SERVEUR
	// On attribue les infos à la socket
	if( bind(sock, (struct sockaddr*)&adresse, sizeof(adresse)) == -1 ){
		cerr << "[NETWORK] Impossible d'ouvrir la socket sur le port " << port << endl;
		FermerSocket();
	}
	#endif
	
	getIP(ip);

	cout << "[NETWORK] ip: " << ip << endl;
	cout << "[NETWORK] port: " << port << endl;
}

// Fermeture d'une socket
void Network::FermerSocket(){

	// On ferme la socket
	closesocket(sock);

	// On quitte Winsock (windows seulement)
#ifdef _WIN32
	WSACleanup();
#endif

	cout << "[NETWORK] Fermeture de la socket reussie !" << endl;

	return;
}

void Network::EnvoyerPaquet(char *to, char *donnees, int longueur){
	int retour = -1;

	// Conversion de l'adresse ip du destinataire
	*(int *)(struct sockaddr*)&adresse.sin_addr = inet_addr(to);

	cout << "Paquet a envoyer: " << donnees << endl;
	
	// On envoie le paquet
	retour = sendto (sock, donnees, longueur, 0, (struct sockaddr*)&adresse, sizeof(adresse) );

	if (retour == -1) {
		cerr << "[NETWORK] Impossible d'envoyer un paquet" << endl;
	}
}

void Network::RecevoirPaquet(char *from, char *donnees){
	int retour = -1;
	int l;

	l = sizeof(adresse);
	retour = recvfrom (sock, donnees, MAX_LONGUEUR_PAQUET, 0, (struct sockaddr*)&adresse, (socklen_t *)&l);

	if(retour >= MAX_LONGUEUR_PAQUET){
		cerr << "[NETWORK] Paquet trop gros recu" << endl;
	}

	// on récupère l'adresse IP de l'émetteur du paquet
	strcpy(from, inet_ntoa(adresse.sin_addr));
}

void Network::getIP(char *ip){
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

//@Charles - c'est super moche, à changer
requete_s to_enum(const string &req){
	if(req == "1")
		return CTS_CONNEXION;
	else if(req == "2")
		return CTS_DECONNEXION;
	else if(req == "1000")
		return STC_CONNEXION;
	else if(req == "1001")
		return STC_DECONNEXION;
	else
		return STC_CTS_NOTHING;
}

void Network::ParserRequete(char *from, char *requete){
	vector<string> req;
	requete_s cmd;

	cout << "Paquet recu: " << requete << " venant de la machine: " << from << endl;

	// Le premier argument est la commande. Les autres arguments
	// sont les données
	boost::iter_split(req, requete, boost::first_finder("^C"));

	cmd = to_enum(req[0]);

	// Paquets venant du client et étant destinés au serveur
	switch(cmd){
		case CTS_CONNEXION:
			cout << "paquet de connexion recu venant du client " << from << "!" << endl;
			#ifdef SERVEUR
			Joueur::Instance().traiterDemandeConnexion(from);
			#endif
			break;

		case CTS_DECONNEXION:
			cout << "paquet de deconnexion recu venant du client " << from << "!" << endl;
			#ifdef SERVEUR
			Joueur::Instance().traiterDemandeDeconnexion(from);
			#endif
			break;

		case STC_CONNEXION:
			cout << "paquet de connexion recu venant du serveur " << from << "!" << endl;
			break;

		case STC_DECONNEXION:
			cout << "paquet de deconnexion recu venant du serveur " << from << "!" << endl;
			break;

		default:
			break;
	}
}
