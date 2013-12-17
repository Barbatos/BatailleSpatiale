#ifndef DETAIL_BATIMENT_HPP
#define DETAIL_BATIMENT_HPP
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeBatiment.hpp"

/**
 * \brief Défini les différents attributs du batiment
 *
 */
struct DetailBatiment {
    TypeBatiment type; ///< Le type du batiment
    sf::Int32 niveau; ///< Le niveau du batiment
    sf::Int32 attaque; ///< L'attaque du batiment
    sf::Int32 vie; ///< La vie courante
    sf::Int32 vieMax; ///< La vie maximum
    sf::Int32 bouclier; ///< Le bouclier courant
    sf::Int32 bouclierMax; ///< Le bouclier maximum
    float bouclierTaux; ///< Le taux de dégats pris par le bouclier
    sf::Int32 visibilite; ///< Le rayon de visibilité
    sf::Int32 rayonAttaque; ///< Le rayon d'attaque
};

#endif
