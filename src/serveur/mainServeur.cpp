#include "../global.hpp"
#include "../core/NetworkGlobal.hpp"
#include "../core/NetworkServer.hpp"

int main()
{
	NetworkServer* serveur;
	unsigned int port = 1337;
	string msg = "";

	cout << "Vous êtes sur le point de lancer un serveur pour le jeu BattleStar." << endl;
	cout << "Veuillez entrer le port sur lequel lancer le serveur [" << port << "]" << endl;

	getline(cin, msg);
	
	if(!msg.empty()){
		port = atoi(msg.c_str());
	}

	serveur = new NetworkServer(port);

	while(true){
		serveur->acceptNewClient();
		sf::sleep(sf::milliseconds(50));
	}

	return 0;
}
