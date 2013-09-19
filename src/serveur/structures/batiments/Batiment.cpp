#include "Batiment.hpp"
#include "TypeBatiment.hpp"

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

const TypeBatiment Batiment::getType(){
	return type;
}
