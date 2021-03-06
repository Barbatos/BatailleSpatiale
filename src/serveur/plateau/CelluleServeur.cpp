#include "CelluleServeur.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/batiments/BatimentEnergieServeur.hpp"
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

sf::Int32 CelluleServeur::getIdJoueur() {
    if(!vaisseau && !batiment)
        return -2;
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
    vaisseau.reset(new VaisseauServeur(80, 20, 0.2f, 3, 40, 3, 25, 3, 10, 10, type));
}

void CelluleServeur::creerVaisseau(TypeVaisseau type) {
    switch (type) {
        case TypeVaisseau::Constructeur:
            vaisseau.reset(new VaisseauServeur(40, 10, 0.1f, 2, 20, 2, 25, 2, 10, 10, type));
            break;

        case TypeVaisseau::Chasseur:
            vaisseau.reset(new VaisseauServeur(110, 22, 0.1f, 3, 45, 3, 25, 3, 10, 10, type));
            break;

        case TypeVaisseau::Croiseur:
            vaisseau.reset(new VaisseauServeur(140, 15, 0.2f, 3, 55, 3, 30, 3, 10, 10, type));
            break;

        case TypeVaisseau::Destructeur:
            vaisseau.reset(new VaisseauServeur(200, 35, 0.2f, 2, 70, 2, 50, 2, 25, 30, type));
            break;

        case TypeVaisseau::Bombardier:
            vaisseau.reset(new VaisseauServeur(1000, 200, 0.3f, 5, 100, 10, 20, 4, 10, 10, TypeVaisseau::Bombardier));
            break;

        case TypeVaisseau::Leger:
        default:
            vaisseau.reset(new VaisseauServeur(80, 20, 0.2f, 3, 40, 3, 25, 3, 10, 10, type));
            break;
    
    }
}

void CelluleServeur::creerVaisseauConstructeurTest() {
    vaisseau.reset(new VaisseauServeur(40, 10, 0.1f, 2, 20, 2, 25, 2, 10, 10, TypeVaisseau::Constructeur));
}

void CelluleServeur::creerVaisseauBombardier() {
}

void CelluleServeur::creerBatimentBase() {
    batiment.reset(new BatimentServeur(800, 50, 0.1f, 5, 0, 0, 10, 4, 10, TypeBatiment::Base));
}

void CelluleServeur::creerBatimentEnergieTest() {
    batiment.reset(new BatimentEnergieServeur(100, 50, 0.1f, 2, 0, 0, 10, 10, 10, 10));
}

void CelluleServeur::creerBatiment(TypeBatiment type) {
    switch (type) {
        case TypeBatiment::Base:
            batiment.reset(new BatimentServeur(800, 70, 0.3f, 5, 0, 0, 5, 4, 10, type));
            break;

        case TypeBatiment::Mine:
        default:
            batiment.reset(new BatimentEnergieServeur(200, 40, 0.1f, 2, 0, 0, 0, 3, 10, 10));
            break;

        case TypeBatiment::ChantierSpatial:
            batiment.reset(new BatimentServeur(400, 60, 0.2f, 5, 0, 0, 3, 4, 10, type));
            // TODO EQUILIBRAGE
            break;

        case TypeBatiment::Raffinerie:
            batiment.reset(new BatimentServeur(300, 40, 0.1f, 5, 0, 0, 3, 4, 10, type));
            // TODO EQUILIBRAGE
            break;
    }
}

void CelluleServeur::creerEvenementTest(TypeEvenement type) {
    evenement.reset(new EvenementServeur(type, true, -1, 1, 1));
}

Structure CelluleServeur::getAttaquant() {
    if(vaisseau)
        return *vaisseau;
    else
        return *batiment;
}

int CelluleServeur::distanceMaximale(sf::Int32 energie) const {
    if(vaisseau)
        return vaisseau->distanceMaximale(energie);
    else
        return 0;
}

int CelluleServeur::visibiliteMaximale() const {
    if(vaisseau)
        return vaisseau->getVisibilite();
    if(batiment)
        return batiment->getVisibilite();
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

int CelluleServeur::attaquer(CelluleServeur *cCible) {
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
        degat *= evenement->getMultiplicateurDegat();
    }

    return cCible->defendre(degat);
}

int CelluleServeur::defendre(int degat) {
    int degatBouclier;
    int degatStructure;

    if(evenement) {
        degat *= evenement->getMultiplicateurDommage();
    }

    if (vaisseau) {
        degatBouclier = degat - vaisseau->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        vaisseau->setBouclier(vaisseau->getBouclier() - degatBouclier);
        vaisseau->setVie(vaisseau->getVie() - degatStructure);
        
        if(vaisseau->getVie() <= 0) {
            vaisseau.reset();
            return 0;
        }
        return vaisseau->getVie();
    } else if (batiment) {
        degatBouclier = degat - batiment->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        batiment->setBouclier(batiment->getBouclier() - degatBouclier);
        batiment->setVie(batiment->getVie() - degatStructure);
        if(batiment->getVie() <= 0) {
            batiment.reset();
            return 0;
        }
        return batiment->getVie();
    } else
        return -1;
}
