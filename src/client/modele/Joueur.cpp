#include "Joueur.hpp"

Joueur::Joueur(string _pseudo, string _ip, sf::Uint16 _id,
               sf::Int32 _commandement, sf::Int32 _requisition, sf::Int32 _energie,
               sf::Int32 _materiaux) :
    pseudo(_pseudo),
    ip(_ip),
    id(_id),
    commandement(_commandement),
    requisition(_requisition),
    energie(_energie),
    materiaux(_materiaux) {

}

string Joueur::getPseudo(void) {
    return this->pseudo;
}

string Joueur::getIp(void) {
    return this->ip;
}

sf::Uint16 Joueur::getId(void) {
    return this->id;
}

sf::Int32 Joueur::getCommandement(void) {
    return this->commandement;
}

sf::Int32 Joueur::getRequisition(void) {
    return this->requisition;
}

sf::Int32 Joueur::getEnergie(void) {
    return this->energie;
}

sf::Int32 Joueur::getMateriaux(void) {
    return this->materiaux;
}
