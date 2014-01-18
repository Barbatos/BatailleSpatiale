#include "Cellule.hpp"
#include <memory>

Cellule::Cellule()
                : type(TypeCellule::Vide) {

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

void Cellule::echangerVaisseau(Cellule& cellule) {
    std::swap(vaisseau, cellule.getReferenceVaisseau());
}

VaisseauPtr& Cellule::getReferenceVaisseau() {
    return vaisseau;
}

void Cellule::setType(TypeCellule _type) {
    type = _type;
}

bool Cellule::getParcourable() const {
    return bits.estParcourable;
}

void Cellule::setParcourable(bool parcourable) {
    bits.estParcourable = parcourable;
}

sf::Packet& operator >>(sf::Packet& paquet, Cellule& cellule) {
    sf::Uint16 typeCellule;
    paquet >> typeCellule;
    cellule.setType(static_cast<TypeCellule>(typeCellule));

    bool existeEvenement;
    paquet >> existeEvenement;
    if (existeEvenement) {
        Evenement* evenement = new Evenement();
        paquet >> *evenement;
        cellule.setEvenement(evenement);
    }
    else {
        cellule.retirerEvenement();
    }

    bool existeVaisseau;
    paquet >> existeVaisseau;
    if (existeVaisseau) {
        Vaisseau* vaisseau = new Vaisseau();
        paquet >> *vaisseau;
        cellule.setVaisseau(vaisseau);
    }
    else {
        cellule.retirerVaisseau();
    }

    bool existeBatiment;
    paquet >> existeBatiment;
    if (existeBatiment) {
        Batiment* batiment = new Batiment();
        paquet >> *batiment;
        cellule.setBatiment(batiment);
    }
    else {
        cellule.retirerBatiment();
    }

    return paquet;
}

TypeCellule Cellule::statutEmplacement() const {
    if (!vaisseau && !batiment)
        if (evenement)
            // Si il n'y a pas de structure mais un evenement qui bloque
            return TypeCellule::Evenement;
        else
            // Si il n'y a pas de structure ni d'évenement
            return type;
    else if (vaisseau)
        return TypeCellule::Vaisseau;
    else
        return TypeCellule::Batiment;
}
