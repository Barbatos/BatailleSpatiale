#include "../global.hpp"

NetworkClient::NetworkClient(void){
	sf::IPAddress server("127.0.0.1");
	
	const unsigned short port = 1337;

	// On se connecte au serveur
	if (socket.Connect(port, server) != sf::Socket::Done){
		cout << "[NETWORK] Impossible de se connecter au serveur !" << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	socket.SetBlocking(false);

	cout << "[NETWORK] Connecté au serveur " << server << std::endl;
}
