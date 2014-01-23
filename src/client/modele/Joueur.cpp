#include "Joueur.hpp"

Joueur::Joueur(string _pseudo, sf::Int32 _commandement, sf::Int32 _requisition,
               sf::Int32 _energie, sf::Int32 _materiaux) :
    pseudo(_pseudo),
    commandement(_commandement),
    requisition(_requisition),
    energie(_energie),
    materiaux(_materiaux) {

}

string Joueur::getPseudo(void) {
    return this->pseudo;
}

void Joueur::setPseudo(string _pseudo) {
    pseudo = _pseudo;
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

sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur) {
    paquet >> joueur.pseudo >> joueur.commandement >> joueur.requisition
           >> joueur.energie >> joueur.materiaux;

    return paquet;
}
