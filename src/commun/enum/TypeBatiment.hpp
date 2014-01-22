#ifndef TYPE_BATIMENT_HPP
#define TYPE_BATIMENT_HPP
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/**
 * \brief Défini les différents types de batiment
 *
 */
enum class TypeBatiment :sf::Uint16 {
	Inexistant,
	Base,
	Mine,
	Raffinerie,
	ChantierSpatial,
	Nombre
};

#endif
