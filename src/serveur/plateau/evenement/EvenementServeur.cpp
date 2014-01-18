#include "EvenementServeur.hpp"

EvenementServeur::EvenementServeur(TypeEvenement _typeEvenement, bool _destructible,
    sf::Int32 _coutDeplacement, sf::Int32 _multiplicateurDommage, sf::Int32 _multiplicateurDegat) {
    type = _typeEvenement;
    destructible = _destructible;
    coutDeplacement = _coutDeplacement;
    multiplicateurDommage = _multiplicateurDommage;
    multiplicateurDegat = _multiplicateurDegat;
}

EvenementServeur::~EvenementServeur() {

}

TypeEvenement EvenementServeur::quelType() {
    return type;
}

bool EvenementServeur::estDestructible() {
    return destructible;
}

bool EvenementServeur::estAccessible() {
    return coutDeplacement != -1;
}

bool EvenementServeur::tirPossible() {
    return multiplicateurDommage != 0;
}

bool EvenementServeur::ciblePossible() {
    return multiplicateurDegat != 0;
}

sf::Int32 EvenementServeur::getCoutDeplacement() {
    return coutDeplacement;
}

sf::Int32 EvenementServeur::getMultiplicateurDommage() {
    return multiplicateurDommage;
}

sf::Int32 EvenementServeur::getMultiplicateurDegat() {
    return multiplicateurDegat;
}

sf::Packet& operator <<(sf::Packet& paquet, const EvenementServeur& evenement) {
    return paquet << static_cast<sf::Uint16>(evenement.type) << evenement.coutDeplacement << evenement.multiplicateurDommage << evenement.multiplicateurDegat << evenement.destructible;
}
