#include <iostream>
#include "Structure.hpp"

int Structure::taille = 100;

// Constructeur
Structure::Structure(int _vieMax, int _bouclierMax, float _bouclierTaux, int _visibilite, int _attaque){

    vie = vieMax = _vieMax;

    bouclier = bouclierMax = _bouclierMax;

    bouclierTaux = _bouclierTaux;

    visibilite = _visibilite;

    attaque = _attaque;

}

 int Structure::getVie() const{
    return vie;
}

 int Structure::getVieMax() const{
    return vieMax;
}

 int Structure::getBouclier() const{
    return bouclier;
}

 int Structure::getBouclierMax() const{
    return bouclierMax;
}

 float Structure::getBouclierTaux() const{
    return bouclierTaux;
}

 int Structure::getVisibilite() const{
    return visibilite;
}

 int Structure::getAttaque() const{
    return attaque;
}

void Structure::setVie(int const _vie){

    if(vie < 0) vie = 0;
    else if(_vie <= vieMax) vie = _vie;
    else vie = vieMax;

}

void Structure::setVieMax(int const _vieMax){

    vieMax = _vieMax;

}

/*
 *  Cette methode renvoie le parametre passe si celui ci est negatif
 *  pour savoir de combien le bouclier a ete depasse si jamais on recoit
 *  des degats
 */

int Structure::setBouclier(int const _bouclier){

    if(_bouclier < 0){
        std::cout << -_bouclier << " degats n'ont pas pu etre absorbes par le bouclier, qui est de " << bouclier << std::endl<< std::endl;
        bouclier = 0;
        return -_bouclier; // On met un - pour avoir une valeur positive
    }
    else if((_bouclier <= bouclierMax)){
        std::cout << "Le _bouclier absorbe " << (bouclier - _bouclier) << " degats" << std::endl << std::endl;
        bouclier = _bouclier;
    }
    else bouclier = bouclierMax;

    return 0;
}


void Structure::setBouclierMax(int const _bouclierMax){

    bouclierMax = _bouclierMax;

}

void Structure::setBouclierTaux(float const _bouclierTaux){

    bouclierTaux = _bouclierTaux;

}

void Structure::setVisibilite(int const _visibilite){

    visibilite = _visibilite;

}

void Structure::setAttaque(int const _attaque){

    attaque = _attaque;

}

/* Cette methode sert a ajouter ou a retirer un certain
 * nombre de points de vie a une structure ciblee    */
void Structure::modifierVie(int const valeur){
    if(vie + valeur < vieMax){
        setVie(vie + valeur);

        if(valeur > 0) std::cout << "La structure est reparee pour " << valeur << " points de vie" << std::endl << std::endl;
        if(valeur < 0) std::cout << "La structure subit " << -valeur << " degats" << std::endl << std::endl;
    }
    else setVie(vieMax);
}


Structure Structure::cloner(Structure const& modele, TechnologieStructure techS){
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
