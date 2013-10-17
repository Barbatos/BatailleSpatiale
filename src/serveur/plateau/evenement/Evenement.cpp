#include <iostream>
#include "Evenement.hpp"

<<<<<<< HEAD
Evenement::Evenement(TypeEvenement::type _typeEvenement, bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat) {
	typeEvenement = _typeEvenement;
=======
Evenement::Evenement() {
	name = "insert event name";
	destructible = -1;
	coutDeplacement = -1;
	multiplicateurDommage = -1;
	multiplicateurDegat = -1;
}

Evenement::Evenement(char* _name, bool _destructible, int _coutDeplacement, int _multiplicateurDommage, int _multiplicateurDegat) {
	name = _name;
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
	destructible = _destructible;
	coutDeplacement = _coutDeplacement;
	multiplicateurDommage = _multiplicateurDommage;
	multiplicateurDegat = _multiplicateurDegat;

<<<<<<< HEAD
	if((destructible == true) != (coutDeplacement == -1))
		std::cout << "Erreur ! un évenement destructible est traversable !!";
}

TypeEvenement::type Evenement::quelType() {
	return typeEvenement;
=======
	//if((destructible == true) != (coutDeplacement == -1))
		//cout << "Erreur ! un évenement destructible est traversable !!";
}

char* Evenement::quelNom() {
	return name;
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
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
