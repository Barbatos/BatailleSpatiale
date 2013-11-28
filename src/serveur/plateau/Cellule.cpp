#include "Cellule.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"

Cellule::Cellule(EvenementPtr _evenement, TypeCellule _type) :
    evenement(_evenement), type(_type) {
}

TypeCellule Cellule::getType() const {
    return type;
}

void Cellule::setType(TypeCellule _type) {
    type = _type;
}

bool Cellule::possedeEvenement() const {
    return evenement != 0;
}

bool Cellule::possedeBatiment() const {
    return batiment != 0;
}

bool Cellule::possedeVaisseau() const {
    return vaisseau != 0;
}

bool Cellule::possedeEmplacement(TypeCellule _type) const {
    if(_type == type)
        if(evenement)
            return evenement->estAccessible() && !batiment && !vaisseau;
        else
            return !batiment && !vaisseau;
    else
        return false;
}

TypeCellule Cellule::statutEmplacement() const {
    if(!vaisseau && !batiment)
        if(evenement)
            if(evenement->estAccessible())
                // Si il n'y a pas de structure et que l'evenement laisse construire
                return type;
            else 
                // Si il n'y a pas de structure mais un evenement qui bloque
                return TypeCellule::Evenement;
        else 
            // Si il n'y a pas de structure ni d'évenement
            return type;
    else if(vaisseau)
        return TypeCellule::Vaisseau;
    else
        return TypeCellule::Batiment;
}

int Cellule::getCoutDeplacement() const {
    if((evenement) && (evenement->getCoutDeplacement() != -1)) {
        if(type == TypeCellule::Minerais)
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
        
    if((evenement) && (evenement->getCoutDeplacement() != -1)) {
        if(type == TypeCellule::Minerais)
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

TypeBatiment Cellule::typeBatiment() const {
    if(batiment)
        return batiment->getType();
    else
        return TypeBatiment::Inexistant;
}

void Cellule::creerVaisseauTest() {
    vaisseau.reset(new Vaisseau(80, 20, 0.2f, 0, 20, 5, 25, TypeVaisseau::Simple));
}

void Cellule::creerVaisseauConstructeurTest() {
    vaisseau.reset(new Vaisseau(40, 10, 0.1f, 0, 10, 10, 25, TypeVaisseau::Constructeur));
}

void Cellule::creerBatimentBaseTest() {
    batiment.reset(new Batiment(200, 50, 0.1f, 0, 0, 0, TypeBatiment::Base));
}

/*
void Cellule::subir(Structure const& attaquant) {
    if(vaisseau)
        vaisseau->subir(attaquant);
    if(batiment)
        batiment->subir(attaquant);
}*/

Structure Cellule::getAttaquant(){
    if(vaisseau)
        return *vaisseau;
    else
        return *batiment;
}

int Cellule::distanceMaximale() const {
    if(vaisseau)
        return vaisseau->getDistanceMax();
    else 
        return 0;
}

bool Cellule::estAccessible() const {
    if(evenement)
        return (evenement->estAccessible() && !vaisseau && !batiment);
    else
        return (!vaisseau && !batiment);
}

void Cellule::retirerVaisseau() {
    vaisseau.reset();
}

VaisseauPtr Cellule::getVaisseau() {
    return vaisseau;
}

EvenementPtr Cellule::getEvenement() {
    return evenement;
}

BatimentPtr Cellule::getBatiment() {
    return batiment;
}

void Cellule::setVaisseau(VaisseauPtr _vaisseau) {
    vaisseau = _vaisseau;
}
