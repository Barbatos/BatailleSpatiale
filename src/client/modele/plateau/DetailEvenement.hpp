#ifndef DETAIL_EVENEMENT_HPP
#define DETAIL_EVENEMENT_HPP
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeEvenement.hpp"

/**
 * \brief Défini les différents attributs de l'évènement
 *
 */
struct DetailEvenement {
    // Nature de l'évènements.
    TypeEvenement type;
    // l'évenement est destructible, on remonte une structure qui prend sa place.
    bool destructible;
    // nombre de deplacement a utiliser pour passer par cette case 1 par défaut -1 pour impossible
    sf::Int16 coutDeplacement;
    // paramètre à prendre en compte lors du calcul des dommages infligés par la structure présente.
    sf::Int16 multiplicateurDommage;
    // paramètre à prendre en compte lors du calcul des dommages subits par la structure présente.
    sf::Int16 multiplicateurDegat;
};

#endif
