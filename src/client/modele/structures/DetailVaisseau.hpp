#ifndef DETAIL_VAISSEAU_HPP
#define DETAIL_VAISSEAU_HPP
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeVaisseau.hpp"

/**
 * \brief Défini les différents attributs du vaisseau
 *
 */
struct DetailVaisseau {
    TypeVaisseau type; ///< Le type du vaisseau
    sf::Int32 vie; ///< La vie courante
    sf::Int32 vieMax; ///< La vie maximum
    sf::Int32 bouclier; ///< Le bouclier courant
    sf::Int32 bouclierMax; ///< Le bouclier maximum
    float bouclierTaux; ///< Le taux de dégats pris par le bouclier
    sf::Int32 visibilite; ///< Le rayon de visibilité
    sf::Int32 rayonAttaque; ///< Le rayon d'attaque
    sf::Int32 attaque; ///< L'attaque du vaisseau
    sf::Int32 consommation; /// La consommation en energie a chaque deplacement
    sf::Int32 distanceMax; ///< Le déplacement max pour un tour
};

#endif
