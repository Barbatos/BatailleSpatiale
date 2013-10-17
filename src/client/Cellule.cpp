#include "Cellule.hpp"
#include <memory>

Cellule::Cellule() :
  type(CelluleVide) {
    
}

bool Cellule::possedeEvenement() {
    return evenement != 0;
}

const DetailEvenement& Cellule::getEvenement() {
    return evenement->getDetail();
}

bool Cellule::possedeBatiment() {
    return batiment != 0;
}

const DetailBatiment& Cellule::getBatiment() {
    return batiment->getDetail();
}

bool Cellule::possedeVaisseau() {
    return vaisseau != 0;
}

const DetailVaisseau& Cellule::getVaisseau() {
    return vaisseau->getDetail();
}

void Cellule::echangerVaisseau(Cellule cellule){
    vaisseau.swap(cellule.getPointeurVaisseau());
}

VaisseauPtr Cellule::getPointeurVaisseau(){
    return VaisseauPtr(vaisseau);
}
