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

void Cellule::setEvenement(Evenement* _evenement) {
    evenement.reset(_evenement);
}

void Cellule::retirerEvenement() {
    evenement.reset();
}

bool Cellule::possedeBatiment() {
    return batiment != 0;
}

const DetailBatiment& Cellule::getBatiment() {
    return batiment->getDetail();
}

void Cellule::setBatiment(Batiment* _batiment) {
    batiment.reset(_batiment);
}

void Cellule::retirerBatiment() {
    batiment.reset();
}

bool Cellule::possedeVaisseau() {
    return vaisseau != 0;
}

const DetailVaisseau& Cellule::getVaisseau() {
    return vaisseau->getDetail();
}

void Cellule::setVaisseau(Vaisseau* _vaisseau) {
    vaisseau.reset(_vaisseau);
}

void Cellule::retirerVaisseau() {
    vaisseau.reset();
}

void Cellule::echangerVaisseau(Cellule cellule){
    vaisseau.swap(cellule.getPointeurVaisseau());
}

VaisseauPtr& Cellule::getPointeurVaisseau(){
    return vaisseau;
}
