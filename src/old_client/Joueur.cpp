#include "Joueur.hpp"

Joueur::Joueur(sf::Int32 _id, std::string _nom, sf::Int32 _energie, sf::Int32 _materiaux) :
    id(_id), nom(_nom), energie(_energie), materiaux(_materiaux) {
}

const std::string& Joueur::getNom() const {
    return nom;
}

const sf::Int32& Joueur::getId() const {
    return id;
}

sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur) {
    return paquet >> joueur.id >> joueur.nom >> joueur.energie >> joueur.materiaux;
}
