#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(TypeEvenement::type _typeEvenement, bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat) {
	typeEvenement = _typeEvenement;
	destructible = _destructible;
	coutDeplacement = _coutDeplacement;
	multiplicateurDommage = _multiplicateurDommage;
	multiplicateurDegat = _multiplicateurDegat;

	if((destructible == true) != (coutDeplacement == -1))
		std::cout << "Erreur ! un évenement destructible est traversable !!";
}

TypeEvenement::type Evenement::quelType() {
	return typeEvenement;
}

bool Evenement::estDestructible() {
	return destructible;
}

bool Evenement::estAccessible(){
	return coutDeplacement != -1;
}

bool Evenement::tirPossible(){
	return multiplicateurDommage != 0;
}

bool Evenement::ciblePossible() {
	return multiplicateurDegat != 0;
}
	
int Evenement::getCoutDeplacement(){
	return coutDeplacement;
}

int Evenement::getMultiplicateurDommage(){
	return multiplicateurDommage;
}

int Evenement::getMultiplicateurDegat(){
	return multiplicateurDegat;
}
