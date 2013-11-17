#include "Vaisseau.hpp"

Vaisseau::Vaisseau() : Structure() {

    energie = 2;
    energieMax = 2;
    consommationMax = 1;
    type = VaisseauVide;

}

Vaisseau::Vaisseau(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int _energieMax, int consommationMax, TypeVaisseau _type):
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque){

    energie = energieMax = _energieMax;
    this->consommationMax = consommationMax;
    type = _type;

}

// Getters
int Vaisseau::getEnergie() const{
    return energie;
}

int Vaisseau::getEnergieMax() const{
    return energieMax;
}

int Vaisseau::getConsommationMax() const{
    return consommationMax;
}


// Setters
void Vaisseau::setEnergie(int const energie){

    if(energie < 0) this->energie = 0;
    else if(energie <= energieMax) this->energie = energie;
    else this->energie = energieMax;

}


void Vaisseau::setEnergieMax(int const energieMax){

    this->energieMax = energieMax;

}

void Vaisseau::setConsommationMax(int const consommationMax){

    this->consommationMax = consommationMax;

}

void Vaisseau::modifierEnergie(int const valeur){

    if(energie + valeur < energieMax){
                setEnergie(energie + valeur);
        if(valeur > 0) std::cout << valeur << " points d' energie ont ete rendus au vaisseau" << std::endl << std::endl;
        if(valeur < 0) std::cout << "Le vaisseau a perdu " << -valeur << " points d'energie" << std::endl << std::endl;
    }
    else this->setEnergie(energieMax);

}


void Vaisseau::afficher(std::ostream& fluxSortant) const {

    fluxSortant << "Vie : " << vie << "/" << vieMax << std::endl <<
                                 "Bouclier : " << bouclier << "/" << bouclierMax << std::endl <<
                                 "% degats absorbes : " << (bouclierTaux*100) << "%" << std::endl <<
                                 "Visibilite : " << visibilite << std::endl <<
                                 "Attaque : " << attaque << std::endl <<
                                 "Energie : " << energie << "/" << energieMax << std::endl <<
                                 "Consommation : " << consommationMax << std::endl << std::endl;


}

std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau) {

    Vaisseau.afficher(fluxSortant) ;
    return fluxSortant;

}

void Vaisseau::subir(Vaisseau const& attaquant){

    Vaisseau cAttaquant(attaquant);

    switch(cAttaquant.getType()){

        case VaisseauChasseur :
            switch(_type){
                case VaisseauBombardier :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.75); break;
                case VaisseauCroiseur :  cAttaquant.setAttaque(cAttaquant.getAttaque() / 2); break;
                case VaisseauDestructeur :  cAttaquant.setAttaque(cAttaquant.getAttaque() / 4); break;
                default : break;

            }
        break;

        case VaisseauChasseurLourd :
            switch(_type){
                case VaisseauBombardier :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 2.5); break;
                case VaisseauDestructeur :  cAttaquant.setAttaque(cAttaquant.getAttaque() / 3); break;
                default : break;

            }
        break;


        case VaisseauCroiseur :
            switch(_type){
                case VaisseauChasseur :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 3); break;
                case VaisseauDestructeur : cAttaquant.setAttaque(cAttaquant.getAttaque() / 2); break;
                default : break;
            }

        break;


        case VaisseauTraqueur :
            switch(_type){
                case VaisseauLeger :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 3); break;
                case VaisseauChasseurLourd :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f); break;
                case VaisseauCroiseur :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f); break;
                case VaisseauBombardier :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f); break;
                case VaisseauDestructeur :  cAttaquant.setAttaque(cAttaquant.getAttaque() / 1.5f); break;
                default : break;

            }
        break;


        case VaisseauDestructeur :
            switch(_type){
                case VaisseauLeger :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 4); break;
                case VaisseauTraqueur :  cAttaquant.setAttaque(cAttaquant.getAttaque() * 2); break;
                default : break;

            }
        break;

    default : break;
    }

    Structure::subir(cAttaquant);

}

/*
void Vaisseau::subir(Batiment const& attaquant){
    Structure::subir(attaquant);

}
*/


Vaisseau Vaisseau::cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV){

    Structure base = Structure::cloner(modele, techS);

    return Vaisseau(base.getVieMax(),
                    base.getBouclierMax(),
                    base.getBouclierTaux(),
                    base.getVisibilite(),
                    base.getAttaque(),
                    modele.getEnergieMax() + (modele.getEnergieMax() * 0.5 * techV.getNiveauEnergie()),
                    modele.getConsommationMax() - (modele.getConsommationMax() * 0.1 * techV.getNiveauConsommation()));

}

int Vaisseau::distanceMaximale() const {
    //A modifier plus tard avec la consommation max
    return energie;
}

TypeVaisseau Vaisseau::getType() const {
    return type;
}
