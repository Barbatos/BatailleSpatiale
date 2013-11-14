#include "../global.hpp"
#include "../commun/ReseauGlobal.hpp"
#include "../commun/ReseauServeur.hpp"

int main()
{
	ReseauServeur* serveur;
	unsigned int port = 1337;
	string msg = "";

	cout << "Vous êtes sur le point de lancer un serveur pour le jeu BattleStar." << endl;
	cout << "Veuillez entrer le port sur lequel lancer le serveur [" << port << "]" << endl;

	getline(cin, msg);
	
	if(!msg.empty()){
		port = atoi(msg.c_str());
	}

	serveur = new ReseauServeur(port);

	while(true){
		serveur->AccepterNouveauClient();
		sf::sleep(sf::milliseconds(50));
	}

	return 0;
}
