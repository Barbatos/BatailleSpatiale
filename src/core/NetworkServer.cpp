#include "../global.hpp"

NetworkServer::NetworkServer(void){
	const unsigned short port = 1337;

	// On écoute sur le port défini plus haut
	if (listener.listen(port) != sf::Socket::Done){
		cout << "[NETWORK] Impossible d'écouter sur le port " << port << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	listener.setBlocking(false);

	cout << "[NETWORK] Ecoute sur le port " << port << " en cours..." << endl;
}

void NetworkServer::acceptNewClient(void)
{
	sf::TcpSocket socket;
	char welcomeMessage[] = "Bienvenue cher client !";

	// On attend une connexion
	if (listener.accept(socket) != sf::Socket::Done){
		return;
	}

	// Un client s'est connecté
	cout << "[NETWORK] Nouveau client: " << socket.getRemoteAddress() << endl;

	// On lui dit bonjour
	NetworkGlobal::sendMessage(socket, welcomeMessage);
}
