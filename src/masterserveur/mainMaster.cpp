#include "Master.hpp"

#define SERVEUR 1

int main() {
    unsigned int portServeurs = 1500;
    unsigned int portClients = 1600;
    Master* masterServeur;
    string msg = "";

    cout << "Vous êtes sur le point de lancer un Master Server pour le jeu Bataille Spatiale." << endl;
    cout << "Veuillez entrer le port sur lequel écouter les serveurs de jeu [" << portServeurs << "]" << endl;

    getline(cin, msg);

    if(!msg.empty()) {
        portServeurs = atoi(msg.c_str());
    }

    cout << "Veuillez entrer le port sur lequel écouter les clients de jeu [" << portClients << "]" << endl;

    getline(cin, msg);

    if(!msg.empty()) {
        portClients = atoi(msg.c_str());
    }

    masterServeur = new Master(portServeurs, portClients);

    while(true) {
        masterServeur->ecouterReseau();
        masterServeur->verifierServeursActifs();
        sf::sleep(sf::milliseconds(50));
    }
}
