#include "Batiment.hpp"

Batiment::Batiment() : Structure(){
    niveau = 0;

}

Batiment::Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, TypeBatiment _type) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque){
    this->niveau = niveau;
    type = _type;

}

int Batiment::getNiveau(){
    return niveau;

}

void Batiment::setNiveau(int niveau){
    this->niveau = niveau;

}

TypeBatiment Batiment::getType() const {
        return type;
}

void Batiment::subir(Vaisseau const& attaquant){
    Vaisseau cAttaquant(attaquant);
    switch(cAttaquant.getType()){
        case VaisseauBombardier :
            cAttaquant.setAttaque(cAttaquant.getAttaque() * 2);
        break;

        default : break;
    }

    Structure::subir(cAttaquant);
}

void Batiment::subir(Batiment const& attaquant){
    Batiment cAttaquant(attaquant);
/* ... */
    Structure::subir(cAttaquant);
}
