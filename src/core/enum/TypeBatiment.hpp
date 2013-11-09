#ifndef TYPE_BATIMENT_HPP
#define TYPE_BATIMENT_HPP
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/**
 * \brief Défini les différents types de batiment
 *
 */
enum class TypeBatiment :sf::Int16 {
    Inexistant,
    Base,
    Nombre
};

#endif