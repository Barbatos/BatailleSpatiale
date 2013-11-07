#include "NetworkGlobal.hpp"

bool NetworkGlobal::getMessage(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout){
	sf::SocketSelector selector;

	// On crée un sélecteur dans lequel on place notre socket
	// Cela nous permet d'utiliser la fonction timeout du SocketSelector
	selector.add(socket);

	// Si on reçoit le message avant la fin du timeout
	if(selector.wait(timeout) > 0){
		socket.receive(packet);
		return true;
	}

	// La réception a échoué
	else {
		return false;
	}
}

void NetworkGlobal::sendMessage(sf::TcpSocket& socket, sf::Packet& packet){
	if (socket.send(packet) != sf::Socket::Done){
		cout << "[NETWORK] Erreur lors de l'envoi d'un paquet" << endl;
		return;
	}

	//cout << "[NETWORK] Message envoyé: " << message << endl;
}
