#ifndef MASTER_HPP
#define MASTER_HPP

#include <global.hpp>
#include <algorithm>
#include <commun/ReseauGlobal.hpp>
#include <commun/enum/TypePaquet.hpp>
#include <masterserveur/ServeurMaster.hpp>
#include <masterserveur/ClientMaster.hpp>

class Master {

public:
    Master(unsigned int portServeur, unsigned int portClient);
    void ecouterReseau();
    void verifierServeursActifs();
    void traiterPaquetServeur(ServeurMaster& serveur, sf::Packet paquet);
    void traiterPaquetClient(ClientMaster& client, sf::Packet paquet);
    void majServeur(sf::Packet paquet, ServeurMaster& serveur);
    void supprimerServeur(ServeurMaster& serveur);
    void envoiListeServeurs(ClientMaster& client);

private:

    sf::TcpListener listener;

    sf::TcpListener listenerClients;

    sf::SocketSelector selector;

    vector<ServeurMaster> serveurs;

    vector<ClientMaster> clients;

    sf::Clock timer;
};

#endif
