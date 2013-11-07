#include "NetworkClient.hpp"

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

void NetworkClient::ParseServerPacket(sf::Packet& packet){
	sf::Int16 	packetType;
	string 		message;

	if(packet.getDataSize() <= 0){
		return;
	}
	
	packet >> packetType >> message;

	cout << "server: " << message << endl;
}
