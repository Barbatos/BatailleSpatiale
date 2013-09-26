#include "Cellule.hpp"
#include "../structures/batiments/TypeBatiment.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"

Cellule::Cellule(EvenementPtr _evenement, TypeCellule _type) :
	evenement(_evenement), type(_type) {
}

const TypeCellule Cellule::getType() {
	return type;
}

void Cellule::setType(TypeCellule _type) {
	type = _type;
}

const bool Cellule::possedeEvenement() {
	return evenement != 0;
}

const bool Cellule::possedeEmplacement(TypeCellule _type) {
	if(_type == type)
		if(evenement)
			return evenement->accessible() && !batiment && !vaisseau;
		else
			return !batiment && !vaisseau;
	else
		return false;
}

const TypeCellule Cellule::statutEmplacement(){
	if(!vaisseau && !batiment)
		if(evenement)
			if(evenement->accessible())
				// Si il n'y a pas de structure et que l'evenement laisse construire
				return type;
			else 
				// Si il n'y a pas de structure mais un evenement qui bloque
				return CelluleEvenement;
		else 
			// Si il n'y a pas de structure ni d'évenement
			return type;
	else if(vaisseau)
		return CelluleVaisseau;
	else
		return CelluleBatiment;
}

const int Cellule::getCoutDeplacement() {
	if((evenment) && (evenement->getCoutDeplacement != -1)) {
		if(type == CelluleMinerais)
			if(evenement)
				return evenement->getCoutDeplacement() + 1;
			else
				return 2;
		else
			if(evenement)
				return evenement->getCoutDeplacement();
			else
				return 1;
	}

	else
		return 10000;
		
}

const void Cellule::afficher(sf::RenderWindow& fenetre, int i, int j){
	if(vaisseau)
		vaisseau->afficherGraphiquement(fenetre, i, j);
	if(batiment)
		batiment->afficherGraphiquement(fenetre, i, j);
}

const TypeBatiment Cellule::typeBatiment(){
	if(batiment)
		return batiment->getType();
	else
		return BatimentVide;
}

void Cellule::creerVaisseauTest() {
	vaisseau.reset(new Vaisseau(80, 20, 0.2f, 0, 20, 5, 25, VaisseauSimple));
}

void Cellule::creerVaisseauConstructeurTest() {
	vaisseau.reset(new Vaisseau(40, 10, 0.1f, 0, 10, 10, 25, VaisseauConstructeur));
}

void Cellule::creerBatimentBaseTest() {
	batiment.reset(new Batiment(200, 50, 0.1f, 0, 0, 0, BatimentBase));
}

void Cellule::subir(Structure const& attaquant) {
	if(vaisseau)
		vaisseau->subir(attaquant);
	if(batiment)
		batiment->subir(attaquant);
}

Structure Cellule::getAttaquant(){
	if(vaisseau)
		return *vaisseau;
	else
		return *batiment;
}

const int Cellule::distanceMaximale() {
	if(vaisseau)
		return vaisseau->distanceMaximale();
	else 
		return 0;
}

const bool Cellule::accessible() {
	if(evenement)
		return (evenement->accessible() && !vaisseau && !batiment);
	else
		return (!vaisseau && !batiment);
}

void Cellule::retirerVaisseau() {
	vaisseau.reset();
}

VaisseauPtr Cellule::getVaisseau() {
	return vaisseau;
}

void Cellule::setVaisseau(VaisseauPtr _vaisseau) {
	vaisseau = _vaisseau;
}