#include "../../global.hpp"
#include "../../serveur/joueurs/Joueur.hpp"
#include "../../commun/ReseauGlobal.hpp"
#include "../../commun/ReseauClient.hpp"
#include "../../commun/ReseauServeur.hpp"
#include "../../commun/enum/TypePaquet.hpp"

ReseauClient* 	client;
ReseauServeur* 	serveur;

void WaitForInput(void) {

	for(;;) {
		string s;
		sf::Packet paquet;
		sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEcho);

		getline(cin, s);

		paquet << typePaquet << s;

		ReseauGlobal::EnvoiPaquet(client->socket, paquet);

		sf::sleep(sf::milliseconds(50));
	}

}

void RunServer(unsigned short port) {

	serveur = new ReseauServeur(port);

	for(;;) {
		serveur->ecouterReseau();
		sf::sleep(sf::milliseconds(50));
	}
}

void GetMessageFromServer() {
	for(;;) {
		sf::Packet paquet;
		string message;
		sf::Int32 packetType;

		ReseauGlobal::ReceptionPaquet(client->socket, paquet, sf::seconds(0.01f));
		client->TraiterPaquetServeur(paquet);

		sf::sleep(sf::milliseconds(50));
	}
}

void RunClient(string ip, unsigned short port) {

	sf::Thread clientCinThread(&WaitForInput);
	sf::Thread fromServerThread(&GetMessageFromServer);

	client = new ReseauClient(ip, port);

	fromServerThread.launch();
	clientCinThread.launch();

}

int main() {
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

	if(selection == "s") {

		RunServer(port);
	}

	else {
		cout << "Which IP?" << endl;
		getline(cin, ip);
		cout << "Connecting to " << ip << ":" << port << endl;

		RunClient(ip, port);
	}
}
