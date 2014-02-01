#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <global.hpp>

class Serveur {

public:
    Serveur();
    string getIp();
    unsigned short getPort();
    string getNom();

private:
    string ip;
    unsigned short port;
    string nom;

    friend sf::Packet& operator >>(sf::Packet& paquet, Serveur& serveur);
};

sf::Packet& operator >>(sf::Packet& paquet, Serveur& serveur);

#endif
