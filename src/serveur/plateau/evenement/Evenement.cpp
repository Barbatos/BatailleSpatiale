#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat, TypeEvenement _typeEvenement){
	typeEvenement = _typeEvenement;
	destrucible = _destructible;
	coutDeplacement = _coutDeplacement;
	multiplicateurDommage = _multiplicateurDommage;
	multiplicateurDegat = _multiplicateurDegat

	if((destrucible == true) != (coutDeplacement == -1))
		cout << "Erreur ! un évenement destrucible est traversable !!";
}

TypeEvenement Evenement::quelType() {
	return typeEvenement;
}

bool Evenement::destructible() {
	return destructible;
}

bool Evenement::accessible(){
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