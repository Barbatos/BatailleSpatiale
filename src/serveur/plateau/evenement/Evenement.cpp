#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(TypeEvenement _typeEvenement, bool _destructible, sf::Int32 _coutDeplacement, sf::Int32 _multiplicateurDommage, sf::Int32 _multiplicateurDegat) {
	type = _typeEvenement;
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

sf::Int32 Evenement::getCoutDeplacement() {
	return coutDeplacement;
}

sf::Int32 Evenement::getMultiplicateurDommage() {
	return multiplicateurDommage;
}

sf::Int32 Evenement::getMultiplicateurDegat() {
	return multiplicateurDegat;
}

sf::Packet& operator <<(sf::Packet& paquet, const Evenement& evenement) {
	return paquet << static_cast<sf::Uint16>(evenement.type) << evenement.coutDeplacement
	       << evenement.multiplicateurDommage << evenement.multiplicateurDegat
	       << evenement.destructible;
}
