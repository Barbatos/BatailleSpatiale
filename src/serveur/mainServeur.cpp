#include "mainServeur.hpp"

int main()
{
	ReseauPtr serveur;
	Plateau* plateau;
	unsigned int port = 1337;
	string msg = "";

	cout << "Vous êtes sur le point de lancer un serveur pour le jeu BattleStar." << endl;
	cout << "Veuillez entrer le port sur lequel lancer le serveur [" << port << "]" << endl;

	getline(cin, msg);
	
	if(!msg.empty()){
		port = atoi(msg.c_str());
	}

	plateau = new Plateau(300, 250);
	serveur = ReseauPtr(new ReseauServeur(port, *plateau));

	while(true){
		serveur->AccepterNouveauClient();
		sf::sleep(sf::milliseconds(50));
	}

	return 0;
}
