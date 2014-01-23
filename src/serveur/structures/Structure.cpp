#include <iostream>
#include "Structure.hpp"

// Constructeur
Structure::Structure(sf::Int32 _vieMax, sf::Int32 _bouclierMax, double _bouclierTaux,
                     sf::Int32 _visibilite, sf::Int32 _attaque, sf::Int32 _rayonAttaque) {

    vie = vieMax = _vieMax;
    bouclier = bouclierMax = _bouclierMax;
    bouclierTaux = _bouclierTaux;
    visibilite = _visibilite;
    attaque = _attaque;
    rayonAttaque = _rayonAttaque;
    idJoueur = 1;

}

void Structure::setIdJoueur( sf::Int32 const _id) {
    idJoueur = _id;
}

sf::Int32 Structure::getIdJoueur() {
    return idJoueur;
}

sf::Int32 Structure::getVie() const {
    return vie;
}

sf::Int32 Structure::getVieMax() const {
    return vieMax;
}

sf::Int32 Structure::getBouclier() const {
    return bouclier;
}

sf::Int32 Structure::getBouclierMax() const {
    return bouclierMax;
}

double Structure::getBouclierTaux() const {
    return bouclierTaux;
}

sf::Int32 Structure::getVisibilite() const {
    return visibilite;
}

sf::Int32 Structure::getAttaque() const {
    return attaque;
}

void Structure::setVie(sf::Int32 const _vie) {

    if(vie < 0) vie = 0;
    else if(_vie <= vieMax) vie = _vie;
    else vie = vieMax;

}

void Structure::setVieMax(sf::Int32 const _vieMax) {

    vieMax = _vieMax;

}

/*
 *  Cette methode renvoie le parametre passe si celui ci est negatif
 *  pour savoir de combien le bouclier a ete depasse si jamais on recoit
 *  des degats
 */

sf::Int32 Structure::setBouclier(sf::Int32 const _bouclier) {

    if(_bouclier < 0) {
        std::cout << -_bouclier << " degats n'ont pas pu etre absorbes par le bouclier, qui est de " << bouclier << std::endl<< std::endl;
        bouclier = 0;
        return -_bouclier; // On met un - pour avoir une valeur positive
    } else if((_bouclier <= bouclierMax)) {
        std::cout << "Le _bouclier absorbe " << (bouclier - _bouclier) << " degats" << std::endl << std::endl;
        bouclier = _bouclier;
    } else bouclier = bouclierMax;

    return 0;
}


void Structure::setBouclierMax(sf::Int32 const _bouclierMax) {

    bouclierMax = _bouclierMax;

}

void Structure::setBouclierTaux(double const _bouclierTaux) {

    bouclierTaux = _bouclierTaux;

}

void Structure::setVisibilite(sf::Int32 const _visibilite) {

    visibilite = _visibilite;

}

void Structure::setAttaque(sf::Int32 const _attaque) {

    attaque = _attaque;

}

/* Cette methode sert a ajouter ou a retirer un certain
 * nombre de points de vie a une structure ciblee    */
void Structure::modifierVie(sf::Int32 const valeur) {
    if(vie + valeur < vieMax) {
        setVie(vie + valeur);

        if(valeur > 0) std::cout << "La structure est reparee pour " << valeur << " points de vie" << std::endl << std::endl;
        if(valeur < 0) std::cout << "La structure subit " << -valeur << " degats" << std::endl << std::endl;
    } else setVie(vieMax);
}


/* Cette methode sert à faire baisser la vie de la
 * structure en utilisant l'attaque de l'attaquant
 * repartie entre la vie et le bouclier.
 * Si le bouclier casse alors ce qu'il n'a pas
 * absorbe est envoye a la vie                  */
void Structure::subir(Structure const& attaquant) {

    std::cout << "L'attaquant a une attaque de " << attaquant.getAttaque() << std::endl << std::endl;
    std::cout << (bouclierTaux*100) << "% des degats sont recus par le bouclier et " << (100-(bouclierTaux*100)) << "% sont recus par la sante" << std::endl << std::endl;;
    std::cout << "Soit " << (attaquant.getAttaque() * bouclierTaux ) << " degats recus par le bouclier et " <<  (attaquant.getAttaque() * (1-bouclierTaux)) << " recus par la sante" << std::endl << std::endl;

    /* Le total des degats est compose des degats
    * qui sont attribues a la vie selon le taux
    * d'absorbsion du bouclier + ce que le
    * bouclier n'a pas absorbé                 */
    this->modifierVie( - (attaquant.getAttaque() * (1-bouclierTaux) + ( this->setBouclier( bouclier - (attaquant.getAttaque() * bouclierTaux ) ) ) ) ) ;
}

/* Meme methode en mode ciblage                */
void Structure::attaquer(Structure& cible) const {
    cible.subir(*this);
}

Structure Structure::cloner(Structure const& modele, TechnologieStructure techS) {
    Structure copie(modele.getVieMax() + (modele.getVieMax() * 0.5 * techS.getNiveauVie()),
                    modele.getBouclierMax() + (modele.getBouclierMax() * 0.5 * techS.getNiveauBouclier()),
                    modele.getBouclierTaux() + (0.05 * techS.getNiveauBouclier()),
                    modele.getVisibilite() + (modele.getVisibilite() * 0.5 * techS.getNiveauVisibilite()),
                    modele.getAttaque() + (modele.getAttaque() * 0.5 * techS.getNiveauAttaque()));

    return copie;

}

std::ostream& operator<<(std::ostream& fluxSortant, Structure const&) {
    return fluxSortant;
}
