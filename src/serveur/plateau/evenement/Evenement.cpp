#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(TypeEvenement _type, bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat) {
    type = _type;
    destructible = _destructible;
    coutDeplacement = _coutDeplacement;
    multiplicateurDommage = _multiplicateurDommage;
    multiplicateurDegat = _multiplicateurDegat;
}

TypeEvenement Evenement::quelType() {
    return type;
}

bool Evenement::estDestructible() {
    return destructible;
}

bool Evenement::estAccessible() {
    return coutDeplacement != -1;
}

bool Evenement::tirPossible() {
    return multiplicateurDommage != 0;
}

bool Evenement::ciblePossible() {
    return multiplicateurDegat != 0;
}

sf::Int16 Evenement::getCoutDeplacement() {
    return coutDeplacement;
}

sf::Int16 Evenement::getMultiplicateurDommage() {
    return multiplicateurDommage;
}

sf::Int16 Evenement::getMultiplicateurDegat() {
    return multiplicateurDegat;
}

sf::Packet& operator <<(sf::Packet& paquet, const Evenement& evenement) {
    return paquet << static_cast<sf::Uint16>(evenement.type) << evenement.coutDeplacement
           << evenement.multiplicateurDommage << evenement.multiplicateurDegat
           << evenement.destructible;
}
