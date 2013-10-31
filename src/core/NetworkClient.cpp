#include "../global.hpp"

NetworkClient::NetworkClient(void){
	sf::IpAddress server("127.0.0.1");
	
	const unsigned short port = 1337;

	// On se connecte au serveur
	if (socket.connect(server, port) != sf::Socket::Done){
		cout << "[NETWORK] Impossible de se connecter au serveur !" << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.setBlocking(false);

	cout << "[NETWORK] Connecté au serveur " << server << endl;
}
