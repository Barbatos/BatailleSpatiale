#include "../../global.hpp"
#include "../../serveur/joueurs/Joueur.hpp"
#include "../../commun/ReseauGlobal.hpp"
#include "../../commun/ReseauClient.hpp"
#include "../../commun/ReseauServeur.hpp"
#include "../../commun/enum/TypePaquet.hpp"

ReseauClient* 	client;

void WaitForInput(void) {

	for(;;) {
		string s;
		sf::Packet paquet;
		sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEcho);

		getline(cin, s);

		paquet << typePaquet << s;

		ReseauGlobal::EnvoiPaquet(client->getSocket(), paquet);

		sf::sleep(sf::milliseconds(50));
	}

}

void GetMessageFromServer() {
	for(;;) {

		client->TraiterPaquetServeur();

		sf::sleep(sf::milliseconds(50));
	}
}

void RunClient(string ip, unsigned short port, string pseudo) {

	sf::Thread clientCinThread(&WaitForInput);
	sf::Thread fromServerThread(&GetMessageFromServer);

	client = new ReseauClient();
	client->ConnexionServeur(ip, port);
	client->EnvoyerPseudoServeur(pseudo);

	fromServerThread.launch();
	clientCinThread.launch();

}

int main() {
	unsigned short port = 1337;
	string selection;
	string p;
	string pseudo = "Anonymous";
	string ip = "localhost";

	cout << "TEST RESEAU - CLIENT" << endl;

	cout << "Quelle IP? (" << ip << ")" << endl;
	getline(cin, selection);

	if(!selection.empty()) {
		ip = selection;
	}

	selection = "";

	cout << "Quel port ? (" << port << ")" << endl;
	getline(cin, selection);

	if(!selection.empty()) {
		port = atoi(selection.c_str());
	}

	cout << "Quel est ton pseudo ?" << endl;
	getline(cin, selection);

	if(!selection.empty()) {
		pseudo = selection;
	}

	cout << "Connexion au serveur " << ip << ":" << port << endl;
	RunClient(ip, port, pseudo);
}
