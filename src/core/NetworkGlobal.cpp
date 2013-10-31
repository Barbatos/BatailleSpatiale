#include "../global.hpp"

void NetworkGlobal::getMessage(sf::SocketTCP socket){
	char message[1024];
	size_t taille;

	// On teste si la réception a échoué
	if (socket.Receive(message, sizeof(message), taille) != sf::Socket::Done){
		return;
	}

	// On affiche le message
	cout << "[NETWORK] message: " << message << endl;

	// TODO: traitement du message ici
}

void NetworkGlobal::sendMessage(sf::SocketTCP socket, const char *message){
	if (socket.Send(message, sizeof(message)) != sf::Socket::Done){
		cout << "[NETWORK] Erreur lors de l'envoi du message: " << message << endl;
		return;
	}

	cout << "[NETWORK] Message envoyé: " << message << endl;
}
