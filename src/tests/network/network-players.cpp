#include "../../global.hpp"
#include "../../serveur/joueurs/Joueur.hpp"
#include "../../core/NetworkGlobal.hpp"
#include "../../core/NetworkClient.hpp"
#include "../../core/NetworkServer.hpp"

NetworkClient* 	client;
NetworkServer* 	server;

void WaitForInput(void){

	for(;;){
		string s;
		sf::Packet packet;
		sf::Int16 packetType = (sf::Int16)PACKETTYPE_CLIENT_SAY;

		//cout << endl << "Write something..." << endl;
		getline(cin, s);
		
		packet << packetType << s;

		NetworkGlobal::sendMessage(client->socket, packet);

		sf::sleep(sf::milliseconds(50));
	}

}

void RunServer(unsigned short port){

	server = new NetworkServer(port);

	for(;;){
		server->acceptNewClient();
		sf::sleep(sf::milliseconds(50));
	}
}

void GetMessageFromServer(){
	for(;;){
		sf::Packet packet;
		string message;
		sf::Int16 packetType;

		NetworkGlobal::getMessage(client->socket, packet, sf::seconds(0.01f));
		client->ParseServerPacket(packet);
		
		sf::sleep(sf::milliseconds(50));
	}
}

void RunClient(string ip, unsigned short port){

	sf::Thread clientCinThread(&WaitForInput);
	sf::Thread fromServerThread(&GetMessageFromServer);

	client = new NetworkClient(ip, port);

	fromServerThread.launch();
	clientCinThread.launch();

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
