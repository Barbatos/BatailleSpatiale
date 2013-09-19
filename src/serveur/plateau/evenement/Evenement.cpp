#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat){
	destrucible = _destructible;
	coutDeplacement = _coutDeplacement;
	multiplicateurDommage = _multiplicateurDommage;
	multiplicateurDegat = _multiplicateurDegat

	if((destrucible == true) != (coutDeplacement == -1))
		cout << "Erreur ! un évenement destrucible est traversable !!";
}

bool Evenement::destrucible() {
	return destrucible;
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