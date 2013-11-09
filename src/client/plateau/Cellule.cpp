#include "Cellule.hpp"
#include <memory>

Cellule::Cellule() :
  type(TypeCellule::Vide) {
    
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

void Cellule::setType(TypeCellule _type) {
    type = _type;
}

sf::Packet& operator >>(sf::Packet& paquet, Cellule& cellule) {
    bool existeEvenement;
    paquet >> existeEvenement;
    if(existeEvenement) {
        Evenement* evenement = new Evenement();
        paquet >> *evenement;
        cellule.setEvenement(evenement);
    } else {
        cellule.retirerEvenement();
    }
    
    bool existeVaisseau;
    paquet >> existeVaisseau;
    if(existeVaisseau) {
        Vaisseau* vaisseau = new Vaisseau();
        paquet >> *vaisseau;
        cellule.setVaisseau(vaisseau);
    } else {
        cellule.retirerVaisseau();
    }
    
    bool existeBatiment;
    paquet >> existeBatiment;
    if(existeBatiment) {
        Batiment* batiment = new Batiment();
        paquet >> *batiment;
        cellule.setBatiment(batiment);
    } else {
        cellule.retirerBatiment();
    }
    
    sf::Int16 typeCellule;
    paquet >> typeCellule;
    cellule.setType(static_cast<TypeCellule>(typeCellule));
    return paquet;
}
