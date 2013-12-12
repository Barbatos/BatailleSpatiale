#include "BatimentServeur.hpp"

BatimentServeur::BatimentServeur() : Structure() {
    niveau = 0;

}

BatimentServeur::BatimentServeur(sf::Int16 vieMax, sf::Int16 bouclierMax, float bouclierTaux, sf::Int16 visibilite, sf::Int16 attaque, sf::Int16 niveau, TypeBatiment _type) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque) {
    this->niveau = niveau;
    type = _type;

}

sf::Int16 BatimentServeur::getNiveau() {
    return niveau;

}

void BatimentServeur::setNiveau(sf::Int16 niveau) {
    this->niveau = niveau;

}

TypeBatiment BatimentServeur::getType() const {
    return type;
}

void BatimentServeur::subir(VaisseauServeur const& attaquant) {
    VaisseauServeur cAttaquant(attaquant);
    switch(cAttaquant.getType()) {
    case TypeVaisseau::Bombardier :
        cAttaquant.setAttaque(cAttaquant.getAttaque() * 2);
        break;

    default :
        break;
    }

    Structure::subir(cAttaquant);
}

void BatimentServeur::subir(BatimentServeur const& attaquant) {
    BatimentServeur cAttaquant(attaquant);
    /* ... */
    Structure::subir(cAttaquant);
}

sf::Packet& operator <<(sf::Packet& paquet, const BatimentServeur& batiment) {
    return paquet << static_cast<sf::Uint16>(batiment.type) << batiment.attaque
           << batiment.vie << batiment.vieMax << batiment.visibilite
           << batiment.bouclier << batiment.bouclierMax << batiment.bouclierTaux
           << batiment.niveau;
}
