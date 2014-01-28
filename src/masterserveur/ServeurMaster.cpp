#include "ServeurMaster.hpp"

ServeurMaster::ServeurMaster() : 
    id(-1), socket(NULL), ip(""), port(-1), dernierHeartbeat(sf::Time::Zero) {

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
