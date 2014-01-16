#include "CelluleServeur.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"

CelluleServeur::CelluleServeur(EvenementPtr _evenement, TypeCellule _type) :
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

/**
 * \brief Indique si la cellule est disponible au deplacement
 * Si un vaisseau ou un batiment est present, alors elle retourne faux.
 * De même si un evenement est present alors on indique s'il est accessible
 *
 * \return Si accessible ou non
 */
bool CelluleServeur::possedeEmplacement(TypeCellule _type) const {
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

/**
 * \brief Indique le cout de deplacement de la cellule
 * Si un vaisseau ou un batiment est present, alors elle retourne un grand nombre.
 * De même si un evenement est present et inaccessible.
 * Ainsi l'algorithme ne fera pas passer le vaisseau par cette cellule.
 *
 * \return Le cout de de placement de la cellule.
 */
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

/**
 * \brief Indique le type de batiment de la cellule s'il existe.
 * Si un batiment est present, alors elle retourne le type correspondant.
 *
 * \return Le type de batiment de la cellule.
 */
TypeBatiment CelluleServeur::typeBatiment() const {
    if(batiment)
        return batiment->getType();
    else
        return TypeBatiment::Inexistant;
}

void CelluleServeur::creerVaisseauTest() {
    vaisseau.reset(new VaisseauServeur(80, 20, 0.2f, 0, 20, 5, 25, TypeVaisseau::Chasseur));
}

void CelluleServeur::creerVaisseauConstructeurTest() {
    vaisseau.reset(new VaisseauServeur(40, 10, 0.1f, 0, 10, 10, 25, TypeVaisseau::Constructeur));
}

void CelluleServeur::creerBatimentBaseTest() {
    batiment.reset(new BatimentServeur(200, 50, 0.1f, 0, 0, 0, TypeBatiment::Base));
}

/**
 * \brief Indique la structure de la cellule
 *
 * \return La structure de la cellule.
 */
Structure CelluleServeur::getAttaquant() {
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
int CelluleServeur::distanceMaximale() const {
    if(vaisseau)
        return vaisseau->getDistanceMax();
    else
        return 0;
}

/**
 * \brief Indique si la cellule est accessible
 * S'il n'ya ni vaisseau ni batiment, la cellule est accesible
 * S'il y a un evenement, il peut laisser la cellule accesible
 *
 * \return True pour accessible, False sinon.
 */
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

EvenementPtr CelluleServeur::getEvenement() const {
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


/**
 * \brief Attaque une cellule cible.
 * Les degats sont calculés selon :
 * - une base qui provient de la structure attaquante sur la cellule.
 * - un coefficient multiplicateur par l'evement, s'il existe.
 * - un coefficient en fonction du type d'attaque par rapport à la cible.
 *
 * Ensuite, on appelle defendre qui va faire les modifications sur les parametres de la cible.
 */
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

/**
 * \brief Inflige les degats a la structure de la cellule.
 * Les degats sont calculés selon :
 * - une base qui provient de la cellule attaquante.
 * - un coefficient multiplicateur par l'evement, s'il existe.
 */
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
    }

    if (batiment) {
        degatBouclier = degat - batiment->getBouclierTaux() * degat;
        degatStructure = degat - degatBouclier;
        batiment->setBouclier(batiment->getBouclier() - degatBouclier);
        batiment->setVie(batiment->getVie() - degatStructure);
    }

}
