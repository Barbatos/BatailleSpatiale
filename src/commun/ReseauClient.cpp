#include "ReseauClient.hpp"

ReseauClient::ReseauClient(string ip, unsigned short port){
	sf::IpAddress server(ip);

	// On se connecte au serveur
	if (socket.connect(server, port) != sf::Socket::Done){
		cout << "[RESEAU] Impossible de se connecter au serveur !" << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.setBlocking(false);

	cout << "[RESEAU] Connecté au serveur " << server << endl;
}

void ReseauClient::TraiterPaquetServeur(sf::Packet& paquet){
	sf::Uint16 	typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
	string 		message;

	if(paquet.getDataSize() <= 0){
		return;
	}
	
	paquet >> typePaquet >> message;

	cout << "serveur: " << message << endl;
}
