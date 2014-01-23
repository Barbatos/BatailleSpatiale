#include "ReseauClient.hpp"

ReseauClient::ReseauClient(Plateau& _plateau) :
	ip("none"),
	port(0),
	plateau(_plateau) {
	setActif(false);
}

ReseauClient::~ReseauClient() {

}

void ReseauClient::ConnexionServeur(string ip, unsigned short port) {
	sf::IpAddress server(ip);
	sf::Time timeout = sf::seconds(5);

	if (getActif() == true) {
		cout
		        << "[RESEAU] Vous êtes déjà connecté à un serveur !"
		        << endl;
		return;
	}

	// On se connecte au serveur
	if (socket.connect(server, port, timeout) != sf::Socket::Done) {
		cout
		        << "[RESEAU] Impossible de se connecter au serveur !"
		        << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.setBlocking(false);

	// On définit que le réseau est maintenant actif
	setActif(true);

	cout
	        << "[RESEAU] Connecté au serveur "
	        << server
	        << endl;
}

void ReseauClient::TraiterPaquetServeur(void) {
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
	sf::Packet paquet;
	string message;

	if (!getActif()) {
		return;
	}

	ReseauGlobal::ReceptionPaquet(socket, paquet, sf::seconds(0.00f));

	if (paquet.getDataSize() <= 0) {
		return;
	}

	paquet >> typePaquet;

	switch (static_cast<TypePaquet>(typePaquet)) {

	case TypePaquet::Plateau:
		paquet >> plateau;
		break;

	case TypePaquet::MessageEchoServeur:
		paquet >> message;
		cout
		        << "[SERVEUR] "
		        << message
		        << endl;
		break;

	case TypePaquet::ZoneParcourable:
		parseZoneParcourable(paquet);
		break;

	case TypePaquet::Chemin:
		parseChemin(paquet);
		break;

	case TypePaquet::DeplacerVaisseau:
		deplacerVaisseau(paquet);
		break;

	case TypePaquet::DeplacementVaisseauImpossible:
		break;

	default:
		cout
		        << "[RESEAU] Erreur: paquet de type "
		        << typePaquet
		        << " inconnu"
		        << endl;
		break;
	}
}

/// Après la connexion, on dit bonjour au serveur
/// en lui donnant notre pseudo
void ReseauClient::EnvoyerPseudoServeur(string pseudo) {
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ChangementDeNom);
	sf::Packet paquet;

	paquet
	        << typePaquet
	        << pseudo;

	ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneParcourable(Position p) {
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneParcourable);
	sf::Packet paquet;

	paquet
	        << typePaquet << p;

	ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::parseZoneParcourable(sf::Packet paquet) {
	sf::Int32 tailleZone;
	Position p;

	paquet >> tailleZone;

	for (sf::Int32 i = 0; i < tailleZone; i++) {
		paquet >> p;
		plateau.cellule[p.x][p.y].setParcourable(true);
	}
}

void ReseauClient::parseChemin(sf::Packet paquet) {
	sf::Int32 tailleZone;
	std::list<Position> pos;
	Position p;

	paquet >> tailleZone;

	for (sf::Int32 i = 0; i < tailleZone; i++)
	{
		paquet >> p;
		plateau.cellule[p.x][p.y].setEstChemin(true);
	}
}

void ReseauClient::getChemin(Position depart, Position arrivee) {
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetChemin);
	sf::Packet paquet;

	paquet
	        << typePaquet << depart << arrivee;

	ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderDeplacementVaisseau(Position depart, Position arrivee){
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderDeplacementVaisseau);
	sf::Packet paquet;

	paquet
	        << typePaquet << depart << arrivee;

	ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::deplacerVaisseau(sf::Packet){

}

void ReseauClient::setActif(bool _actif) {
	actif = _actif;
}

bool ReseauClient::getActif(void) {
	return actif;
}

void ReseauClient::setIp(string _ip) {
	ip = _ip;
}

void ReseauClient::setPort(unsigned short _port) {
	port = _port;
}

sf::TcpSocket& ReseauClient::getSocket(void) {
	return socket;
}
