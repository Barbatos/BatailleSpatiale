#ifndef TYPE_VAISSEAU_HPP
#define TYPE_VAISSEAU_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/**
 * \brief Défini les différents types de vaisseau
 *
 */
enum class TypeVaisseau : sf::Uint16 {
    Inexistant,
    Constructeur,
    Bombardier,
    Chasseur,
    Croiseur,
    Destructeur,
    ChasseurLourd,
    Traqueur,
    Leger
};

#endif
