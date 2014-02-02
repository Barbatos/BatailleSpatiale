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
    // Paquet envoyé au serveur pour connaître la zone parcourable à partir d'une case
    GetZoneParcourable,
    // Paquet envoyé par le serveur au client pour définir la zone parcourable
    ZoneParcourable,
    // Paquet envoyé au serveur pour connaître la liste des joueurs adverses
    GetJoueursAdverses,
    // Paquet envoyé au serveur pour connaître les infos du joueur courant
    GetJoueurCourant,
    // Paquet envoyé au client par le serveur contenant la liste des joueurs adverses
    JoueursAdverses,
    // Paquet envoyé au client par le serveur contenant les informations du joueur courant
    JoueurCourant,
    // Paquet envoyé au serveur pour connaître le chemin pour aller d'une position 1 à une position 2
    GetChemin,
    // Paquet envoyé par le serveur au client pour définir le chemin
    Chemin,
    // Paquet envoyé par le client pour demander le déplacement d'un vaisseau
    DemanderDeplacementVaisseau,
    // Paquet envoyé par le serveur au client pour ordonner le déplacement d'un vaisseau
    DeplacerVaisseau,
    // Paquet envoyé par le serveur au client pour indiquer que le déplacement d'un vaisseau est impossible
    DeplacementVaisseauImpossible,
    // Paquet envoyé par le client pour connaître la zone constructible autour d'une case
    GetZoneConstructibleVaisseau,
    GetZoneConstructibleBatiment,
    // Paquet envoyé par le serveur au client pour renseigner la zone constructible
    ZoneConstructibleVaisseau,
    ZoneConstructibleBatiment,
    // Paquet envoyé par le client au serveur pour demander la zone attaquable
    GetZoneAttaquable,
    // Paquet envoyé par le serveur au client pour donner la zone attaquable
    ZoneAttaquable,
    // Paquet envoyé par le client au serveur pour demander l'attaque d'un vaisseau
    DemanderAttaqueVaisseau,
    // Paquet envoyé par le serveur au client pour ordonner l'attaque d'un vaisseau
    AttaquerVaisseau,
    // Paquet envoyé par le serveur au client pour indiquer que l'attaque d'un vaisseau est impossible
    AttaqueVaisseauImpossible,
    // Paquet envoyé par le client au serveur pour demander la liste des vaisseaux constructibles
    GetVaisseauxConstructibles,
    // Paquet envoyé par le serveur au client pour lui envoyer la liste des vaisseaux constructibles
    VaisseauxConstructibles,
    // Paquet envoyé par le serveur au client pour lui indiquer que la partie multijoueurs démarre
    DemarrerPartieMulti,
    // -- Master Serveur -- //
    // Paquet envoyé par un serveur de jeu au Master afin de lui dire qu'il est en vie
    MasterHeartbeat,
    // Paquet envoyé par un serveur de jeu au Master afin de lui dire qu'il se déconnecte
    MasterDeconnexion,
    // Paquet envoyé par un client pour récupérer la liste des serveurs connectés au Master
    MasterGetServeurs,
    // Paquet envoyé par le Master à un client pour donner la liste des serveurs 
    MasterListeServeurs,
    /// Juste pour savoir le nombre de TypePaquet (A placer en fin d'enumerations)
    Nombre
};

#endif
