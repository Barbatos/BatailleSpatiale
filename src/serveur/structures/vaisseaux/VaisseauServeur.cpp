#include "VaisseauServeur.hpp"

VaisseauServeur::VaisseauServeur() :
    Structure(),
    type(),
    distanceMax(0),
    consommation(0)

{
}

VaisseauServeur::VaisseauServeur(sf::Int32 _vieMax, sf::Int32 _bouclierMax, float _bouclierTaux,
                   sf::Int32 _visibilite, sf::Int32 _attaque, sf::Int32 _distanceMax,
                   sf::Int32 _consommation, sf::Int32 _rayonAttaque, sf::Int32 _prixEnergie, sf::Int32 _prixMateriaux, TypeVaisseau _type) :
    Structure(_vieMax, _bouclierMax, _bouclierTaux, _visibilite, _attaque, _rayonAttaque, _prixEnergie, _prixMateriaux),
    type(_type),
    distanceMax(_distanceMax),
    consommation(_consommation)

{
}

sf::Int32 VaisseauServeur::getConsommation() const {
    return consommation;
}

// Setters

void VaisseauServeur::setConsommation(const sf::Int32 _consommation) {
    consommation = _consommation;
}

void VaisseauServeur::afficher(std::ostream& fluxSortant) const {

    fluxSortant
            << "Vie : "
            << vie
            << "/"
            << vieMax
            << std::endl
            << "Bouclier : "
            << bouclier
            << "/"
            << bouclierMax
            << std::endl
            << "% degats absorbes : "
            << (bouclierTaux * 100)
            << "%"
            << std::endl
            << "Visibilite : "
            << visibilite
            << std::endl
            << "Attaque : "
            << attaque
            << std::endl
            << "Consommation : "
            << consommation
            << std::endl
            << "Prix Energie : "
            << prixEnergie
            << std::endl
            << "Prix Materiaux : "
            << prixMateriaux
            << std::endl
            << std::endl;

}

std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur) {

    VaisseauServeur.afficher(fluxSortant);
    return fluxSortant;

}


// il faut équilibrer les valeurs, rajouter les cas de certains types ...
int VaisseauServeur::triangulaire(VaisseauServeurPtr vAttaquant) {

    switch (vAttaquant->getType()) {

    case TypeVaisseau::Chasseur:
        switch (type) {
        case TypeVaisseau::Bombardier:
            return 2;
            break;
        case TypeVaisseau::Croiseur:
            return 10;
            break;
        case TypeVaisseau::Destructeur:
            return 80;
            break;
        default:
            break;
        }
        break;

    case TypeVaisseau::ChasseurLourd:
        switch (type) {
        case TypeVaisseau::Bombardier:
            return 2;
            break;
        case TypeVaisseau::Croiseur:
            return 10;
            break;
        case TypeVaisseau::Destructeur:
            return 80;
            break;
        default:
            break;
        }
        break;

    case TypeVaisseau::Croiseur:
        switch (type) {
        case TypeVaisseau::Bombardier:
            return 2;
            break;
        case TypeVaisseau::Croiseur:
            return 10;
            break;
        case TypeVaisseau::Destructeur:
            return 80;
            break;
        default:
            break;
        }
        break;

    case TypeVaisseau::Traqueur:
        switch (type) {
        case TypeVaisseau::Bombardier:
            return 2;
            break;
        case TypeVaisseau::Croiseur:
            return 10;
            break;
        case TypeVaisseau::Destructeur:
            return 80;
            break;
        default:
            break;
        }
        break;

    case TypeVaisseau::Destructeur:
        switch (type) {
        case TypeVaisseau::Bombardier:
            return 2;
            break;
        case TypeVaisseau::Croiseur:
            return 10;
            break;
        case TypeVaisseau::Destructeur:
            return 80;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    return 1;
}

/*
 void VaisseauServeur::subir(BatimentServeur const& attaquant){
 Structure::subir(attaquant);

 }
 */

VaisseauServeur VaisseauServeur::cloner(VaisseauServeur const& modele, TechnologieStructure techS,
                          TechnologieVaisseau techV) {

    Structure base = Structure::cloner(modele, techS);

    return VaisseauServeur(
               base.getVieMax(),
               base.getBouclierMax(),
               base.getBouclierTaux(),
               base.getVisibilite(),
               base.getAttaque(),
               base.getRayonAttaque(),
               base.getPrixEnergie(),
               base.getPrixMateriaux(),
               modele.getDistanceMax() + (modele.getDistanceMax() * 0.5 * techV
                                          .getNiveauDistance()),
               modele.getConsommation() - (modele.getConsommation() * 0.1 * techV
                                           .getNiveauConsommation()));

}

sf::Int32 VaisseauServeur::getDistanceMax() const {
    return distanceMax;
}

TypeVaisseau VaisseauServeur::getType() const {
    return type;
}

sf::Packet& operator <<(sf::Packet& paquet, const VaisseauServeur& vaisseau) {
    return paquet << static_cast<sf::Uint16>(vaisseau.type) << vaisseau.attaque
           << vaisseau.vie << vaisseau.vieMax << vaisseau.visibilite << vaisseau.rayonAttaque
           << vaisseau.bouclier << vaisseau.bouclierMax << vaisseau.bouclierTaux
           << vaisseau.consommation << vaisseau.distanceMax << vaisseau.idJoueur << vaisseau.prixEnergie << vaisseau.prixMateriaux;
}


