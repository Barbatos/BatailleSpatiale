#include <iostream>
#include "Plateau.hpp"

int main() {

	const std::string quitter = "exit";

	std::string message = "";

	// On lance la connexion ici le port par défaut est 50001
	// On aurais pu ecrire plateau("127.0.0.1", 50001)
	Plateau plateau("127.0.0.1");

	sf::Socket::Status statut = sf::Socket::Done;

	std::cout << "Entrez votre pseudo" << std::endl;
	std::getline(std::cin,message);

	plateau.renommerJoueur(message);

	std::cout << "Entrez le message à envoyer \"exit\" pour quitter" << std::endl;
	while(message != quitter && statut == sf::Socket::Done) {
		std::getline(std::cin,message);

		std::string commande = message.substr(0, message.find_first_of(' '));

		if(commande == "/nom") {
			if(message.size() < commande.size() + 2) {
				std::cout << "Vous devez entrer un nouveau pseudo !" << std::endl;
			}

			std::string nouveauNom = message.substr(message.find_first_of(' ') + 1);

			plateau.renommerJoueur(nouveauNom);
		} else if(commande == "/joueurs") {
			std::cout << " Liste des joueurs" << std::endl;
			std::cout << "-------------------" << std::endl;
			for(Joueur* j : plateau.getJoueurs())
				std::cout << j->getNom() << std::endl;
			std::cout << "-------------------" << std::endl;
		} else if(message != quitter)
			statut = plateau.envoyerMessagePourTous(message);
	}

	return EXIT_SUCCESS;
}
