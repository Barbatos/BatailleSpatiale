#include "Entrepot.hpp"

Entrepot::Entrepot(int _energie, int _energieMax):
	BatimentServeur::BatimentServeur(), energie(_energie), energieMax(_energieMax) {
}

/*Entrepot::Entrepot(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, int energieMax) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, niveau){

    niveau = this->energieMax = energieMax;

}*/

int Entrepot::getEnergie(){
    return energie;

}

// Ajoute de l'energie a l'entrepot et renvoie l'energie non utilisé
int Entrepot::ajouterEnergie(int ajout){
	if(energieMax - energie >= ajout){
		energie += ajout;
		return 0;
	} else {
		ajout = energieMax - energie;
		energie = energieMax;
		return ajout;
	}
}

// retire de l'energie et renvoie l'energie non retiré
int Entrepot::retirerEnergie(int retrait){
	if(energie >= retrait){
		energie -= retrait;
		return 0;
	} else {
		retrait = energie;
		energie = 0;
		return retrait;
	}
}

int Entrepot::getEnergieMax(){
    return energieMax;

}

void Entrepot::setEnergie(int _energie){
    energie = _energie;

}

void Entrepot::setEnergieMax(int _energieMax){
    energieMax = _energieMax;
}
