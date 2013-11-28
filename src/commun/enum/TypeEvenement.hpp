#ifndef TYPE_EVENEMENT_HPP
#define TYPE_EVENEMENT_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/**
 * \brief Défini les différents types de l'évènement
 *
 */
enum class TypeEvenement :sf::Uint16 {
    Inexistant,
    ChampMeteor,
    Epave,
    InfluenceTrouNoir,
    NuageGaz,
    StationSpatialeAbandonnee,
    Nombre
};

#endif
