#ifndef DETAIL_EVENEMENT_HPP
#define DETAIL_EVENEMENT_HPP
#include <SFML/System.hpp>
#include "../../core/enum/TypeEvenement.hpp"

/**
 * \brief Défini les différents attributs de l'évènement
 *
 */
struct DetailEvenement {
    TypeEvenement type;///< Le type de l'évènement
    sf::Int32 vie;///<La vie de l'obstacle -1 si il n'a pas de vie
    sf::Int32 coutDeplacement;///<Le cout du deplacement pour traverser cette case
    sf::Int32 multiplicateurAttaque;///<Le coefficient multiplicateur des dégats engrangés
    sf::Int32 multiplicateurDegat;///<Le coefficient multiplicateur des dégats subis
};

#endif
