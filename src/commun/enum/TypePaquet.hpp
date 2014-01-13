#ifndef TYPE_PAQUET_HPP
#define TYPE_PAQUET_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/**
 * \brief Défini les différents types de paquets
 *
 */
enum class TypePaquet : sf::Uint16 {
    /// Si le typePaquet est vide détruire le reste du paquet
    // TypePaquet
    Vide,
    /// Message provenant du serveur
    // TypePaquet, message(std::string)
    MessageEchoServeur,
    /// Message servant juste à être affiché
    // TypePaquet, message(std::string)
    MessageEcho,
    /// Ping demandé par l'autre bout du socket
    // TypePaquet
    PING,
    /// Pong renvoyé à l'autre bout du socket
    // TypePaquet
    PONG,
    /// Informe le client du numero de joueur(id du client)
    // TypePaquet, idJoueur(sf::Int32)
    NumeroJoueur,
    /// Informe le client du changement d'un joueur
    // TypePaquet, idJoueur(sf::Int32), joueur(Joueur)
    ActualiserJoueur,
    /// Informe le client de la suppression d'un joueur
    // TypePaquet, idJoueur(sf::Int32)
    SupprimerJoueur,
    /// Informe le client du changement du plateau
    // TypePaquet, plateau(Plateau)
    Plateau,
    /// Informe le client du changement d'un nouveau joueur
    // TypePaquet, joueur(Joueur)
    Joueur,
    /// Paquet envoyé au serveur pour demander la modification du nom
    // TypePaquet, nom(std::string)
    ChangementDeNom,
    /// Juste pour savoir le nombre de TypePaquet
    Nombre,

    EnvoiPseudoServeur, /// Le premier paquet envoyé au serveur après la connexion, envoi du pseudo du joueur

    GetZoneParcourable,

    ZoneParcourable,
};

#endif
