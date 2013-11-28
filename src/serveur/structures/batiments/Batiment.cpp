#include "Batiment.hpp"

Batiment::Batiment() : Structure() {
    niveau = 0;

}

Batiment::Batiment(sf::Int16 vieMax, sf::Int16 bouclierMax, float bouclierTaux, sf::Int16 visibilite, sf::Int16 attaque, sf::Int16 niveau, TypeBatiment _type) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque) {
    this->niveau = niveau;
    type = _type;

}

sf::Int16 Batiment::getNiveau() {
    return niveau;

}

void Batiment::setNiveau(sf::Int16 niveau) {
    this->niveau = niveau;

}

TypeBatiment Batiment::getType() const {
    return type;
}

void Batiment::subir(Vaisseau const& attaquant) {
    Vaisseau cAttaquant(attaquant);
    switch(cAttaquant.getType()) {
    case TypeVaisseau::Bombardier :
        cAttaquant.setAttaque(cAttaquant.getAttaque() * 2);
        break;

    default :
        break;
    }

    Structure::subir(cAttaquant);
}

void Batiment::subir(Batiment const& attaquant) {
    Batiment cAttaquant(attaquant);
    /* ... */
    Structure::subir(cAttaquant);
}

sf::Packet& operator <<(sf::Packet& paquet, const Batiment& batiment) {
    return paquet << static_cast<sf::Uint16>(batiment.type) << batiment.attaque
           << batiment.vie << batiment.vieMax << batiment.visibilite
           << batiment.bouclier << batiment.bouclierMax << batiment.bouclierTaux
           << batiment.niveau;
}
