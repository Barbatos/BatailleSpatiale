#include "JoueurServeur.hpp"

JoueurServeur::JoueurServeur(void) :
    socket(NULL), pseudo("Anonymous"), ip(""), id(-1),
    commandement(0), requisition(0), energie(0), materiaux(0) {
        techS = TechnologieStructure();
        techB = TechnologieBatiment();
        techV = TechnologieVaisseau();

}

sf::TcpSocket* JoueurServeur::getSocket(void) {
    return this->socket;
}

string JoueurServeur::getPseudo(void) {
    return this->pseudo;
}

string JoueurServeur::getIp(void) {
    return this->ip;
}

sf::Uint16 JoueurServeur::getId(void) {
    return this->id;
}

sf::Int16 JoueurServeur::getCommandement(void) {
    return this->commandement;
}

sf::Int16 JoueurServeur::getRequisition(void) {
    return this->requisition;
}

sf::Int32 JoueurServeur::getEnergie(void) {
    return this->energie;
}

sf::Int32 JoueurServeur::getMateriaux(void) {
    return this->materiaux;
}

void JoueurServeur::setSocket(sf::TcpSocket* _socket) {
    this->socket = _socket;
}

void JoueurServeur::setPseudo(string _pseudo) {
    this->pseudo = _pseudo;
}

void JoueurServeur::setIp(string _ip) {
    this->ip = _ip;
}

void JoueurServeur::setId(sf::Uint16 _id) {
    this->id = _id;
}

void JoueurServeur::setCommandement(sf::Int16 _commandement) {
    this->commandement = _commandement;
}

void JoueurServeur::setRequisition(sf::Int16 _requisition) {
    this->requisition = _requisition;
}

void JoueurServeur::setEnergie(sf::Int32 _energie) {
    this->energie = _energie;
}

void JoueurServeur::setMateriaux(sf::Int32 _materiaux) {
    this->materiaux = _materiaux;
}
