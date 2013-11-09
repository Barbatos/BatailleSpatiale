#include <iostream>
#include "plateau/Plateau.hpp"

int main() {

    const std::string quitter = "exit";

    std::string message = "";
    
    Plateau plateau("127.0.0.1");
    
    sf::Socket::Status statut = sf::Socket::Done;
    
    std::cout << "Entrez votre pseudo" << std::endl;
    std::getline(std::cin,message);
    
    plateau.renommerJoueur(message);

    std::cout << "Entrez le message à envoyer \"exit\" pour quitter" << std::endl;
    while(message != quitter && statut == sf::Socket::Done) {
        std::getline(std::cin,message);

        if(message != quitter)
            statut = plateau.envoyerMessagePourTous(message);
    }
    
    return EXIT_SUCCESS;
}
