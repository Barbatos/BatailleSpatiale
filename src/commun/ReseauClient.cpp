#include "ReseauClient.hpp"

ReseauClient::ReseauClient(void){
	setActif(false);
}

void ReseauClient::ConnexionServeur(string ip, unsigned short port){
	sf::IpAddress server(ip);

	if(getActif() == true){
		cout << "[RESEAU] Vous êtes déjà connecté à un serveur !" << endl;
		return;
	}

	// On se connecte au serveur
	if (socket.connect(server, port) != sf::Socket::Done){
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
	string 		message;
	sf::Packet 	paquet;

	if(!getActif()){
		return;
	}

	ReseauGlobal::ReceptionPaquet(socket, paquet, sf::seconds(0.00f));

	if(paquet.getDataSize() <= 0){
		return;
	}
	
	paquet >> typePaquet >> message;

	cout << "serveur: " << message << endl;
}

void ReseauClient::setActif(bool _actif){
	actif = _actif;
}

bool ReseauClient::getActif(void){
	return actif;
}
