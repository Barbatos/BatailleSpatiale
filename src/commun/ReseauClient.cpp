#include "ReseauClient.hpp"

ReseauClient::ReseauClient(Plateau& _plateau) : 
	ip("none"), port(0), plateau(_plateau) 
{
	setActif(false);
}

ReseauClient::~ReseauClient(){

}

void ReseauClient::ConnexionServeur(string ip, unsigned short port){
	sf::IpAddress server(ip);
	sf::Time timeout = sf::seconds(5);

	if(getActif() == true){
		cout << "[RESEAU] Vous êtes déjà connecté à un serveur !" << endl;
		return;
	}

	// On se connecte au serveur
	if (socket.connect(server, port, timeout) != sf::Socket::Done){
		cout << "[RESEAU] Impossible de se connecter au serveur !" << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.setBlocking(false);

	// On définit que le réseau est maintenant actif
	setActif(true);

	cout << "[RESEAU] Connecté au serveur " << server << endl;
}

void ReseauClient::TraiterPaquetServeur(void){
	sf::Uint16 	typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
	sf::Packet 	paquet;
	string 		message;

	if(!getActif()){
		return;
	}

	ReseauGlobal::ReceptionPaquet(socket, paquet, sf::seconds(0.00f));

	if(paquet.getDataSize() <= 0){
		return;
	}

	paquet >> typePaquet;

	switch(static_cast<TypePaquet>(typePaquet)){

		case TypePaquet::Plateau:
			paquet >> plateau;
			break;

		case TypePaquet::MessageEchoServeur:
		default:
			paquet >> typePaquet >> message;
			cout << "[SERVEUR] " << typePaquet << ", " << message << endl;
			break;
	}
}

/// Après la connexion, on dit bonjour au serveur
/// en lui donnant notre pseudo
void ReseauClient::EnvoyerPseudoServeur(string pseudo){
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::EnvoiPseudoServeur);
	sf::Packet paquet;

	paquet << typePaquet << pseudo;

	ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::setActif(bool _actif){
	actif = _actif;
}

bool ReseauClient::getActif(void){
	return actif;
}

void ReseauClient::setIp(string _ip){
	ip = _ip;
}

void ReseauClient::setPort(unsigned short _port){
	port = _port;
}

sf::TcpSocket& ReseauClient::getSocket(void){
	return socket;
}

