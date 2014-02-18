#include "Serveur.hpp"

Serveur::Serveur() :
        ip(""), port(-1), nom("Serveur sans nom") {

}

string Serveur::getIp() const {
    return ip;
}

unsigned short Serveur::getPort() const {
    return port;
}

string Serveur::getNom() const {
    return nom;
}

sf::Packet& operator >>(sf::Packet& paquet, Serveur& serveur) {
    paquet >> serveur.ip >> serveur.port >> serveur.nom;

    return paquet;
}
