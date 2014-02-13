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
     * \param nom le nom du serveur
     * \param partieSolo définit si on joue une partie solo (vs IA) ou pas
     */
    ReseauServeur(unsigned short port, PlateauServeur& plateau, string nom, bool partieSolo);
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

    void envoiZoneParcourable(JoueurServeur& joueur, Position pos);

    void envoiJoueurCourant(JoueurServeur& joueur);
    
    void envoiJoueursAdverses(JoueurServeur& joueur);

    void envoiChemin(JoueurServeur& joueur, Position posDepart, Position posArrivee);

    void deplacerVaisseau(JoueurServeur& joueur, Position posDepart, Position posArrivee);

    void envoiZoneConstructibleVaisseau(JoueurServeur& joueur);

    void envoiZoneConstructibleBatiment(JoueurServeur& joueur, Position pos);

    void envoiZoneAttaquable(JoueurServeur& joueur, Position pos);

    void creerBase(JoueurServeur& joueur, int nbJoueurs);

    void envoiPlateauATous();

    void attaquerVaisseau(JoueurServeur& joueur, Position posAttaquant, Position posCible);

    void envoiHeartbeat();

    void envoiVaisseauxConstructibles(JoueurServeur& joueur);

    void demarrerPartieMulti();

    void joueurSuivant();

    void envoiPaquetATous(sf::Packet paquet);

    void envoiZoneVisible(JoueurServeur& joueur);

private:

    /// La socket du serveur
    sf::TcpListener listener;

    /// La socket du serveur pour l'interaction avec le Master Serveur
    sf::TcpSocket socketMaster;

    /// Le sélecteur qui permet d'écouter toutes les sockets ouvertes
    sf::SocketSelector selector;

    /// Liste des joueurs connectés
    vector<JoueurServeur> joueurs;

    PlateauServeur& plateau;

    sf::Thread reseauThread;

    sf::Clock timer;

    sf::Time dernierHeartbeat;

    string nom;
    
    bool actif;

    unsigned short port;

    bool partieSolo;

    sf::Int32 joueurActuel;
};

typedef std::shared_ptr<ReseauServeur> ReseauServeurPtr;

#endif
