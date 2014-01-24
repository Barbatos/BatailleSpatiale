#include "CelluleServeur.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"

CelluleServeur::CelluleServeur(EvenementServeurPtr _evenement, TypeCellule _type) :
    evenement(_evenement), type(_type) {
}

TypeCellule CelluleServeur::getType() const {
    return type;
}

void CelluleServeur::setType(TypeCellule _type) {
    type = _type;
}

bool CelluleServeur::possedeEvenement() const {
    return evenement != 0;
}

bool CelluleServeur::possedeBatiment() const {
    return batiment != 0;
}

bool CelluleServeur::possedeVaisseau() const {
    return vaisseau != 0;
}

bool CelluleServeur::possedeEmplacement(TypeCellule _type) const {
    if(_type == type)
        if(evenement)
            return evenement->estAccessible() && !batiment && !vaisseau;
        else
            return !batiment && !vaisseau;
    else
        return false;
}

TypeCellule CelluleServeur::statutEmplacement() const {
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

sf::Uint16 CelluleServeur::getIdJoueur() {
    if(!vaisseau && !batiment)
        return -1;
    else if(vaisseau)
        return vaisseau->getIdJoueur();
    else
        return batiment->getIdJoueur();
}

int CelluleServeur::getCoutDeplacement() const {
    if(!evenement || (evenement->getCoutDeplacement() != -1)) {
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

TypeBatiment CelluleServeur::typeBatiment() const {
    if(batiment)
        return batiment->getType();
    else
        return TypeBatiment::Inexistant;
}

void CelluleServeur::creerVaisseauTest(TypeVaisseau type) {
    vaisseau.reset(new VaisseauServeur(80, 20, 0.2f, 0, 20, 5, 25, 10, 10, 10, type));
}

void CelluleServeur::creerVaisseauConstructeurTest() {
    vaisseau.reset(new VaisseauServeur(40, 10, 0.1f, 0, 10, 10, 25, 10, 10, 10, TypeVaisseau::Constructeur));
}

void CelluleServeur::creerBatimentBase() {
    batiment.reset(new BatimentServeur(200, 50, 0.1f, 0, 0, 0, 10, 10, 10, TypeBatiment::Base));
}

Structure CelluleServeur::getAttaquant() {
    if(vaisseau)
        return *vaisseau;
    else
        return *batiment;
}

int CelluleServeur::distanceMaximale() const {
    if(vaisseau)
        return vaisseau->getDistanceMax();
    else
        return 0;
}

int CelluleServeur::attaqueMaximale() const {
    if(vaisseau)
        return vaisseau->getRayonAttaque();
    if(batiment)
        return batiment->getRayonAttaque();
    else
        return 0;
}

bool CelluleServeur::estAccessible() const {
    if(type == TypeCellule::Inexistant)
        return false;
    if(evenement)
        return (evenement->estAccessible() && !vaisseau && !batiment);
    else
        return (!vaisseau && !batiment);
}

void CelluleServeur::retirerVaisseau() {
    vaisseau.reset();
}

VaisseauServeurPtr CelluleServeur::getVaisseau() const {
    return vaisseau;
}

VaisseauServeurPtr& CelluleServeur::getVaisseauPtr() {
    return vaisseau;
}

void CelluleServeur::echangerVaisseau(CelluleServeur& cellule) {
    std::swap(vaisseau, cellule.getVaisseauPtr());
}

EvenementServeurPtr CelluleServeur::getEvenement() const {
    return evenement;
}

BatimentServeurPtr CelluleServeur::getBatiment() const {
    return batiment;
}

void CelluleServeur::setVaisseau(VaisseauServeurPtr _vaisseau) {
    vaisseau = _vaisseau;
}

sf::Packet& operator <<(sf::Packet& paquet, const CelluleServeur& cellule) {
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

void CelluleServeur::attaquer(CelluleServeur *cCible) {
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

void CelluleServeur::defendre(int degat) {
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
    } else if (batiment) {
        degatBouclier = degat - batiment->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        batiment->setBouclier(batiment->getBouclier() - degatBouclier);
        batiment->setVie(batiment->getVie() - degatStructure);
    }

}
