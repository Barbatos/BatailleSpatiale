#include "../../global.hpp"
#include "../../serveur/joueurs/Joueur.hpp"
#include "../../core/NetworkGlobal.hpp"
#include "../../core/NetworkClient.hpp"
#include "../../core/NetworkServer.hpp"

NetworkClient* client;
NetworkServer* server;

void WaitForInput(void){
	string s;
	sf::Packet packet;
	int packetType = (int)PACKETTYPE_CLIENT_SAY;

	cout << "Please write something to send..." << endl;
	getline(cin, s);
	
	packet << packetType << s;

	NetworkGlobal::sendMessage(client->socket, packet);

}

void RunServer(unsigned short port){

	server = new NetworkServer(port);

	for(;;){
		server->acceptNewClient();
		usleep(1000*100); // 100ms
	}
}

void RunClient(string ip, unsigned short port){
	sf::Packet packet;
	string message;
	int packetType = (int)PACKETTYPE_CLIENT_SAY;

	client = new NetworkClient(ip, port);

	cout << "Entrez votre pseudo!" << endl;
	getline(cin, message);

	packet << packetType << message;
	NetworkGlobal::sendMessage(client->socket, packet);

	for(;;){
		NetworkGlobal::getMessage(client->socket, packet, sf::seconds(0.01f));
		packet >> message;
		if(!message.empty()){
			cout << "[NETWORK] Message du serveur: " << message << endl;
		}
		WaitForInput();
	}
}

int main(){
	unsigned short port = 1337;
	string selection;
	string p;
	string ip = "localhost";

	cout << "NETWORK TEST - CLIENT-SERVER" << endl;

	cout << "Wanna launch a client (c) or a server (s) ?" << endl;
	getline(cin, selection);

	cout << "Which port ?" << endl;
	getline(cin, p);
	port = atoi(p.c_str());

	if(selection == "s"){

		RunServer(port);
	}

	else {
		cout << "Which IP?" << endl;
		getline(cin, ip);
		cout << "Connecting to " << ip << ":" << port << endl;

		RunClient(ip, port);
	}
}
