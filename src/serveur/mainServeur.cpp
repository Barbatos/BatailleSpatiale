#include "mainServeur.hpp"

#define SERVEUR 1

int main() {
    ReseauServeurPtr serveur;
    PlateauServeur* plateau;
    unsigned int port = 1337;
    string msg = "";
    string nom = "Serveur sans nom";

    cout << "Vous êtes sur le point de lancer un serveur pour le jeu BattleStar." << endl;
    cout << "Veuillez entrer le port sur lequel lancer le serveur [" << port << "]" << endl;

    getline(cin, msg);

    if(!msg.empty()) {
        port = atoi(msg.c_str());
    }

    cout << "Veuillez entrer un nom pour votre serveur [" << nom << "]" << endl;

    getline(cin, msg);
    
    if(!msg.empty()) {
        nom = msg.c_str();
    }

    plateau = new PlateauServeur(15, 15);
    serveur = ReseauServeurPtr(new ReseauServeur(port, *plateau, nom, false));

    while(true) {
        serveur->ecouterReseau();
        sf::sleep(sf::milliseconds(50));
    }

    return 0;
}
