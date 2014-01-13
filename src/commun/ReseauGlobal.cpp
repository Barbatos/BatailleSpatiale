#include "ReseauGlobal.hpp"

bool ReseauGlobal::ReceptionPaquet(sf::TcpSocket& socket, sf::Packet& paquet, sf::Time timeout){
	if(socket.receive(paquet)){
		return true;
	}

	else {
		return false;
	}
}

void ReseauGlobal::EnvoiPaquet(sf::TcpSocket& socket, sf::Packet& paquet){
	if (socket.send(paquet) != sf::Socket::Done){
		cout << "[RESEAU] Erreur lors de l'envoi d'un paquet" << endl;
		return;
	}
}
