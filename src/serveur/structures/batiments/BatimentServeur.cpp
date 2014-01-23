#include "BatimentServeur.hpp"

BatimentServeur::BatimentServeur() : Structure() {
    niveau = 0;

}

BatimentServeur::BatimentServeur(sf::Int32 vieMax, sf::Int32 bouclierMax, float bouclierTaux, sf::Int32 visibilite, sf::Int32 attaque, sf::Int32 niveau, sf::Int32 rayonAttaque, sf::Int32 prixEnergie, sf::Int32 prixMateriaux, TypeBatiment _type) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, rayonAttaque, prixEnergie, prixMateriaux) {
    this->niveau = niveau;
    type = _type;

}

sf::Int32 BatimentServeur::getNiveau() {
    return niveau;

}

void BatimentServeur::setNiveau(sf::Int32 niveau) {
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
           << batiment.vie << batiment.vieMax << batiment.visibilite << batiment.rayonAttaque
           << batiment.bouclier << batiment.bouclierMax << batiment.bouclierTaux
           << batiment.niveau << batiment.idJoueur << batiment.prixEnergie << batiment.prixMateriaux;
}


