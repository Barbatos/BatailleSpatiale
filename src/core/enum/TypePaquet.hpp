#ifndef TYPE_PAQUET_HPP
#define TYPE_PAQUET_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/**
 * \brief Défini les différents types de paquets
 *
 */
enum class TypePaquet : sf::Uint16 {
    Vide,
    MessageEchoServeur,
    MessageEcho,
    PING,
    PONG,
    NumeroJoueur,
    Plateau,
    Joueur,
    ChangementDeNom,
    ActualiserJoueur,
    Nombre
};

#endif
