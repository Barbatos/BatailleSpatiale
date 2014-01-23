#ifndef _RESEAU_SERVER_H_
#define _RESEAU_SERVER_H_

#include "../global.hpp"
#include "../serveur/joueurs/JoueurServeur.hpp"
#include "../commun/ReseauGlobal.hpp"
#include "../commun/enum/TypePaquet.hpp"
#include "../serveur/plateau/PlateauServeur.hpp"

/**
 * Classe permettant de démarrer un serveur de jeu
 * et de gérer les clients qui s'y connectent.
 */
class ReseauServeur {

public:

    /**
     * \brief Constructeur par défaut
     *
     * \param port le port du serveur
     * \param plateau le plateau de jeu
     */
    ReseauServeur(unsigned short port, PlateauServeur& plateau);
    /**
     * \brief Fonction gérant les paquets envoyés au serveur par des
     * clients extérieurs.
     */
    void ecouterReseau(void);

    /**
     * \brief Fonction permettant de traiter un paquet reçu d'un client.
     *
     * \param paquet le paquet reçu
     */
    void traiterPaquetClient(JoueurServeur& joueur, sf::Packet paquet);

    /**
     * \brief Envoi d'un message par le serveur à tous les clients
     *
     * \param message le message à envoyer
     */
    void envoiATous(string& message);

    /**
     * \brief Envoi d'un message par le serveur à un unique client
     *
     * \param client la socket du client
     * \param message le message à envoyer
     */
    void envoiUnique(sf::TcpSocket& client, string& message);

    /**
     * \brief Envoi du plateau à un client
     *
     * \param client la socket du client
     * \param plateau le plateau
     */
    void envoiPlateau(sf::TcpSocket& client, PlateauServeur& _plateau);

    void setPlateau(PlateauServeur& plateau);

    void threadReseau();

    void lancerReseau();

    void fermerReseau();

    void envoiZoneParcourable(sf::TcpSocket& client, Position pos);

    void envoiJoueursAdverses(JoueurServeur& joueur);

    void envoiChemin(sf::TcpSocket& client, Position posDepart, Position posArrivee);

    void deplacerVaisseau(sf::TcpSocket& client, Position posDepart, Position posArrivee);

    void envoiZoneConstructible(sf::TcpSocket& client, Position pos);

private:

    /// La socket du serveur
    sf::TcpListener listener;

    /// Le sélecteur qui permet d'écouter toutes les sockets ouvertes
    sf::SocketSelector selector;

    /// Liste des joueurs connectés
    vector<JoueurServeur> joueurs;

    PlateauServeur& plateau;

    sf::Thread reseauThread;

    bool actif;
};

typedef std::shared_ptr<ReseauServeur> ReseauServeurPtr;

#endif
