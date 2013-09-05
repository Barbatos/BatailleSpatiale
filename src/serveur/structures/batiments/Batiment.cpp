#include "Batiment.hpp"

Batiment::Batiment() : Structure(){
    niveau = 0;

}

Batiment::Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque){
    this->niveau = niveau;

}

int Batiment::getNiveau(){
    return niveau;

}

void Batiment::setNiveau(int niveau){
    this->niveau = niveau;

}
