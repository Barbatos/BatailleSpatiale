#include "Cellule.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"

// constructeur
Cellule::Cellule(EvenementPtr _evenement, TypeCellule _type) :
    evenement(_evenement), type(_type) {
}

// getters
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

Structure Cellule::getAttaquant(){
    if(vaisseau)
        return *vaisseau;
    else
        return *batiment;
}

VaisseauPtr Cellule::getVaisseau() {
    return vaisseau;
}

BatimentPtr Cellule::getBatiment() {
    return batiment;
}

int Cellule::getAttaqueCellule() {
    int dommage = 0;
    
    if(vaisseau)
        dommage = vaisseau->getAttaque();
    if (batiment)
        dommage = batiment->getAttaque();
    if(evenement)
        dommage *= evenement->getMultiplicateurDommage();

    return dommage;
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

// Setters
void Cellule::setType(TypeCellule _type) {
    type = _type;
}

void Cellule::setVaisseau(VaisseauPtr _vaisseau) {
    vaisseau = _vaisseau;
}

bool Cellule::possedeEvenement() const {
    return evenement != 0;
}

// autres
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
                return CelluleEvenement;
        else 
            // Si il n'y a pas de structure ni d'évenement
            return type;
    else if(vaisseau)
        return CelluleVaisseau;
    else
        return CelluleBatiment;
}


TypeBatiment Cellule::typeBatiment() const {
    if(batiment)
        return batiment->getType();
    else
        return BatimentVide;
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



// BUG
int Cellule::degatTriangleVaisseauVaisseau(VaisseauPtr vAttaquant) {


    switch(vAttaquant->getType()){

        case VaisseauChasseur :
            switch(getVaisseau()->getType() ){
                case VaisseauBombardier :       return 1; break;
                case VaisseauCroiseur :         return 1; break;
                case VaisseauDestructeur :      return 1; break;
                default : break;

            }
        break;

        case VaisseauChasseurLourd :
            switch(getVaisseau()->getType()){
                case VaisseauBombardier :       return 1; break;
                case VaisseauDestructeur :      return 1; break;
                default : break;

            }
        break;


        case VaisseauCroiseur :
            switch(getVaisseau()->getType()){
                case VaisseauChasseur :         return 3; break;
                case VaisseauDestructeur :      return 1; break;
                default : break;
            }

        break;


        case VaisseauTraqueur :
            switch(getVaisseau()->getType()){
                case VaisseauLeger :            return 3; break;
                case VaisseauChasseurLourd :    return 1; break;
                case VaisseauCroiseur :         return 1; break;
                case VaisseauBombardier :       return 1; break;
                case VaisseauDestructeur :      return 1; break;
                default : break;

            }
        break;


        case VaisseauDestructeur :
            switch(getVaisseau()->getType()){
                case VaisseauLeger :            return 4; break;
                case VaisseauTraqueur :         return 2; break;
                default : break;

            }
        break;

    default :                                   return 1; break;
    }

    return 1;
}




/*
 * la cellule voit si elle est concernée par un évenement.
 * une fois cela vérfifé, elle calcule les dégats en fonction de plusieurs paramètres
 * la force d'attaque de l'attaquant
 * le multiplicateur de dégat possiblement dû par l'évenement
 * [en cours] le système de triangle de dégâts
 * et le taux de bouclier qui lui permet de passer outre un certain pourcentage de dégâts
 */
void Cellule::subirDegat(Cellule cAttaquant) {
    
    int degat = 0;
    //degat += attaquant.getAttaqueCellule(getVaisseau());
    


    if(vaisseau) {
        if(evenement) 
            degat *= evenement->getMultiplicateurDegat();

        vaisseau->modifierVie( vaisseau->getVie() - degat );
        vaisseau->setBouclier( vaisseau->getBouclier() - vaisseau->getBouclierTaux() * degat );

       if(cAttaquant.vaisseau != NULL) {
            
            degat *= degatTriangleVaisseauVaisseau(cAttaquant.getVaisseau());
        }

    }

    if(batiment) {
        if(evenement) 
            degat *= evenement->getMultiplicateurDegat();

        batiment->modifierVie( batiment->getVie() - degat);
        batiment->setBouclier( vaisseau->getBouclier() - vaisseau->getBouclierTaux() * degat );
    }

    else
        std::cout << "ERREUR Cellule::subirDegat();" << std::endl;
}

// méthodes "tests"
void Cellule::creerVaisseauTest() {
    vaisseau.reset(new Vaisseau(80, 20, 0.2f, 0, 20, 5, 25, VaisseauSimple));
}

void Cellule::creerVaisseauConstructeurTest() {
    vaisseau.reset(new Vaisseau(40, 10, 0.1f, 0, 10, 10, 25, VaisseauConstructeur));
}

void Cellule::creerBatimentBaseTest() {
    batiment.reset(new Batiment(200, 50, 0.1f, 0, 0, 0, BatimentBase));

EvenementPtr Cellule::getEvenement() {
    return evenement;
}

BatimentPtr Cellule::getBatiment() {
    return batiment;
}

void Cellule::setVaisseau(VaisseauPtr _vaisseau) {
    vaisseau = _vaisseau;

}
