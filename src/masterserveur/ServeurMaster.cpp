#include "ServeurMaster.hpp"

ServeurMaster::ServeurMaster() : 
    id(-1), dernierHeartbeat(sf::Time::Zero), socket(NULL), ip(""), port(-1), nom("Serveur sans nom") {

}

int ServeurMaster::getId() {
    return id;
}

sf::TcpSocket* ServeurMaster::getSocket() {
    return socket;
}

sf::IpAddress ServeurMaster::getIp() {
    return ip;
}

unsigned short ServeurMaster::getPort() {
    return port;
}

sf::Time ServeurMaster::getDernierHeartbeat() {
    return dernierHeartbeat;
}

string ServeurMaster::getNom() {
    return nom;
}

void ServeurMaster::setId(int _id) {
    id = _id;
}

void ServeurMaster::setSocket(sf::TcpSocket* _socket) {
    socket = _socket;
}

void ServeurMaster::setIp(sf::IpAddress _ip) {
    ip = _ip;
}

void ServeurMaster::setPort(unsigned short _port) {
    port = _port;
}

void ServeurMaster::setDernierHeartbeat(sf::Time _dernierHeartbeat) {
    dernierHeartbeat = _dernierHeartbeat;
}

void ServeurMaster::setNom(string _nom) {
    nom = _nom;
}

sf::Packet& operator <<(sf::Packet& paquet, const ServeurMaster& serveur) {
    paquet << serveur.ip.toString() << serveur.port << serveur.nom;

    return paquet;
}
