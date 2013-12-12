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

/**
 * \brief Indique si la cellule est disponible au deplacement
 * Si un vaisseau ou un batiment est present, alors elle retourne faux.
 * De même si un evenement est present alors on indique s'il est accessible
 * 
 * \return Si accessible ou non
 */
bool Cellule::possedeEmplacement(TypeCellule _type) const {
    if(_type == type)
        if(evenement)
            return evenement->estAccessible() && !batiment && !vaisseau;
        else
            return !batiment && !vaisseau;
    else
        return false;
}

/**
 * \brief Indique le type de la cellule
 * Si un vaisseau ou un batiment est present, alors elle retourne un type correspondant.
 * De même si un evenement est present.
 * 
 * \return Le type de la cellule.
 */
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

/**
 * \brief Indique le cout de deplacement de la cellule
 * Si un vaisseau ou un batiment est present, alors elle retourne un grand nombre.
 * De même si un evenement est present et inaccessible.
 * Ainsi l'algorithme ne fera pas passer le vaisseau par cette cellule.
 * 
 * \return Le cout de de placement de la cellule.
 */
int Cellule::getCoutDeplacement() const {
    if((evenement) && (evenement->getCoutDeplacement() != -1)) {
        if(type == TypeCellule::Minerais)
            if(evenement)
                return evenement->getCoutDeplacement() + 1;
            else
                return 2;
        else if(evenement)
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
        else if(evenement)
            return evenement->getCoutDeplacement();
        else
            return 1;
    }

    else
        return 10000;

}

/**
 * \brief Indique le type de batiment de la cellule s'il existe.
 * Si un batiment est present, alors elle retourne le type correspondant.
 * 
 * \return Le type de batiment de la cellule.
 */
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

/**
 * \brief Indique la structure de la cellule
 *
 * \return La structure de la cellule.
 */
Structure Cellule::getAttaquant() {
    if(vaisseau)
        return *vaisseau;
    else
        return *batiment;
}

/**
 * \brief Indique la distance maximale du vaisseau sur la cellule.
 * S'il n'y a pas de vaisseau, alors on retourne 0.
 *
 * \return La distance maximale du vaisseau sur la cellule.
 */
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

VaisseauPtr Cellule::getVaisseau() const {
    return vaisseau;
}

EvenementPtr Cellule::getEvenement() const {
    return evenement;
}

BatimentPtr Cellule::getBatiment() const {
    return batiment;
}

void Cellule::setVaisseau(VaisseauPtr _vaisseau) {
    vaisseau = _vaisseau;
}

sf::Packet& operator <<(sf::Packet& paquet, const Cellule& cellule) {
    paquet << static_cast<sf::Uint16>(cellule.getType());
    
    paquet << cellule.possedeEvenement();
    if(cellule.possedeEvenement())
        paquet << *(cellule.getEvenement());

    paquet << cellule.possedeVaisseau();
    if(cellule.possedeVaisseau())
        paquet << *(cellule.getVaisseau());

    paquet << cellule.possedeBatiment();
    if(cellule.possedeBatiment())
        paquet << *(cellule.getBatiment());

    return paquet;
}


void Cellule::attaquer(Cellule *cCible) {
    int degat = 0;

    if (vaisseau) {
        degat += vaisseau->getAttaque();
        if (cCible->getVaisseau()) {
           degat *= vaisseau->triangulaire(cCible->getVaisseau());
        }
    }

    if (batiment) {
        degat += batiment->getAttaque();
    }

    if(evenement) {
        degat *= evenement->getMultiplicateurDommage();
    }

    cCible->defendre(degat);
}

/*
 * La méthode applique les dégats à la cellule, en calculant la part des evenements et du bouclier.
 */
void Cellule::defendre(int degat) {
    int degatBouclier;
    int degatStructure;

    if(evenement) {
        degat *= evenement->getMultiplicateurDegat();
    }

    if (vaisseau) {
        degatBouclier = degat - vaisseau->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        vaisseau->setBouclier(vaisseau->getBouclier() - degatBouclier);
        vaisseau->setVie(vaisseau->getVie() - degatStructure);
    }

    if (batiment) {
        degatBouclier = degat - batiment->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        batiment->setBouclier(batiment->getBouclier() - degatBouclier);
        batiment->setVie(batiment->getVie() - degatStructure);
    }

}
