#include "ReseauGlobal.hpp"

bool ReseauGlobal::ReceptionMessage(sf::TcpSocket& socket, sf::Packet& paquet, sf::Time timeout){
	sf::SocketSelector selecteur;

	// On crée un sélecteur dans lequel on place notre socket
	// Cela nous permet d'utiliser la fonction timeout du SocketSelector
	selecteur.add(socket);

	// Si on reçoit le message avant la fin du timeout
	if(selecteur.wait(timeout) > 0){
		socket.receive(paquet);
		return true;
	}

	// La réception a échoué
	else {
		return false;
	}
}

void ReseauGlobal::EnvoiMessage(sf::TcpSocket& socket, sf::Packet& paquet){
	if (socket.send(paquet) != sf::Socket::Done){
		cout << "[RESEAU] Erreur lors de l'envoi d'un paquet" << endl;
		return;
	}

	//cout << "[NETWORK] Message envoyé: " << message << endl;
}
