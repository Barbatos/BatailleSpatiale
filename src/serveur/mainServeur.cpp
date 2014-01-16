#include "mainServeur.hpp"

int main() {
    ReseauServeurPtr serveur;
    PlateauServeur* plateau;
    unsigned int port = 1337;
    string msg = "";

    cout << "Vous êtes sur le point de lancer un serveur pour le jeu BattleStar." << endl;
    cout << "Veuillez entrer le port sur lequel lancer le serveur [" << port << "]" << endl;

    getline(cin, msg);

    if(!msg.empty()) {
        port = atoi(msg.c_str());
    }

    plateau = new PlateauServeur(300, 250);
    serveur = ReseauServeurPtr(new ReseauServeur(port, *plateau));

    while(true) {
        serveur->ecouterReseau();
        sf::sleep(sf::milliseconds(50));
    }

    return 0;
}
