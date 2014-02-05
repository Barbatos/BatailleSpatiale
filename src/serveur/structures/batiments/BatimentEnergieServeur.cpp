#include "BatimentEnergieServeur.hpp"

BatimentEnergieServeur::BatimentEnergieServeur(sf::Int32 vieMax, sf::Int32 bouclierMax, float bouclierTaux,
 sf::Int32 visibilite, sf::Int32 attaque, sf::Int32 niveau, sf::Int32 rayonAttaque, sf::Int32 prixEnergie,
 sf::Int32 prixMateriaux, sf::Int32 _energieARecolter) :
    BatimentServeur(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, niveau,
        rayonAttaque, prixEnergie, prixMateriaux, TypeBatiment::Raffinerie), energieARecolter(_energieARecolter) {
}

void BatimentEnergieServeur::setEnergieARecolter(const sf::Int32& energieARecolter) {
    this->energieARecolter = energieARecolter;
}

sf::Int32 BatimentEnergieServeur::getEnergieARecolter() const {
    return energieARecolter;
}

sf::Packet& operator <<(sf::Packet& paquet, const BatimentEnergieServeur& batiment) {
    return paquet << (BatimentServeur) batiment << batiment.energieARecolter;
}
