#include "../global.hpp"

NetworkClient::NetworkClient(string ip, unsigned short port){
	sf::IpAddress server(ip);

	// On se connecte au serveur
	if (socket.connect(server, port) != sf::Socket::Done){
		cout << "[NETWORK] Impossible de se connecter au serveur !" << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.setBlocking(false);

	cout << "[NETWORK] Connecté au serveur " << server << endl;
}
