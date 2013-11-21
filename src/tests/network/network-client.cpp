#include "../../global.hpp"
#include "../../serveur/joueurs/Joueur.hpp"
#include "../../commun/ReseauGlobal.hpp"
#include "../../commun/ReseauClient.hpp"
#include "../../commun/ReseauServeur.hpp"
#include "../../commun/enum/TypePaquet.hpp"

ReseauClient* 	client;
ReseauServeur* 	serveur;

void WaitForInput(void){

	for(;;){
		string s;
		sf::Packet paquet;
		sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEcho);

		getline(cin, s);
		
		paquet << typePaquet << s;

		ReseauGlobal::EnvoiPaquet(client->getSocket(), paquet);

		sf::sleep(sf::milliseconds(50));
	}

}

void GetMessageFromServer(){
	for(;;){

		client->TraiterPaquetServeur();
		
		sf::sleep(sf::milliseconds(50));
	}
}

void RunClient(string ip, unsigned short port){

	sf::Thread clientCinThread(&WaitForInput);
	sf::Thread fromServerThread(&GetMessageFromServer);

	client = new ReseauClient();
	client->ConnexionServeur(ip, port);

	fromServerThread.launch();
	clientCinThread.launch();

}

int main(){
	unsigned short port = 1337;
	string selection;
	string p;
	string ip = "localhost";

	cout << "NETWORK TEST - CLIENT" << endl;

	cout << "Which IP?" << endl;
	getline(cin, ip);

	cout << "Which port ?" << endl;
	getline(cin, p);
	port = atoi(p.c_str());

	cout << "Connecting to " << ip << ":" << port << endl;
	RunClient(ip, port);
}
