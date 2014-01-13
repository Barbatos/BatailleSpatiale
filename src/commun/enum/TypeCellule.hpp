#ifndef TYPE_CELLULE_HPP
#define TYPE_CELLULE_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/**
 * \brief Défini les différents types de la cellule
 *
 * Défini si la cellule est une cellule classique ou si elle produit de
 * l'énergie, du minerais, ...
 *
 */
enum class TypeCellule :sf::Uint16 {
    Inexistant,
    Vide,
    Minerais,
    Energie,
    Batiment,
    Evenement,
    Vaisseau,
    Nombre
};

#endif
