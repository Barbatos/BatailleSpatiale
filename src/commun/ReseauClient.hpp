#ifndef _RESEAU_CLIENT_H_
#define _RESEAU_CLIENT_H_

#include "../global.hpp"
#include "ReseauGlobal.hpp"
#include "enum/TypePaquet.hpp"
#include "../client/modele/Plateau.hpp"
#include "../commun/utile/Position.hpp"
#include "../client/modele/Joueur.hpp"

/**
 * Classe qui permet à un client de se connecter à
 * un serveur de jeu et d'envoyer/recevoir des infos.
 */
class ReseauClient {

    public:
        /**
         * \brief Constructeur par défaut
         *
         */
        ReseauClient(Plateau& _plateau, Joueur& _joueur);

        /**
         * \brief Destructeur par défaut
         */
        ~ReseauClient(void);

        /**
         * \brief Connexion à un serveur
         *
         * \param ip l'ip du serveur sur lequel on veut se connecter
         * \param port le port du serveur
         */
        void ConnexionServeur(string ip, unsigned short port);

        void ConnexionMasterServeur(void);

        /**
         * \brief Traite un paquet reçu de la part du serveur
         *
         */
        void TraiterPaquetServeur(void);

        /**
         * \brief Récupère l'état d'activité du client sur le réseau
         *
         * \return si le client est actif ou non
         */
        bool getActif(void);

        /**
         * \brief Définit l'état d'activité du client sur le réseau
         *
         * \param _actif l'état d'activité
         */
        void setActif(bool _actif);

        bool getPartieActive(void);

        void setPartieActive(bool _active);

        sf::TcpSocket& getSocket(void);

        void setIp(string _ip);

        void setPort(unsigned short _port);

        void EnvoyerPseudoServeur(string pseudo);

        void getZoneParcourable(Position p);

        void parseZoneParcourable(sf::Packet paquet);

        void getChemin(Position depart, Position arrivee);

        void parseChemin(sf::Packet paquet);

        void deplacerVaisseau(sf::Packet paquet);

        void demanderDeplacementVaisseau(Position depart, Position arrivee);

        void getZoneConstructibleVaisseau(Position p);

        void getZoneConstructibleBatiment(Position p);

        void parseZoneConstructibleVaisseau(sf::Packet paquet);

        void parseZoneConstructibleBatiment(sf::Packet paquet);

        void getZoneAttaquable(Position p);

        void parseZoneAttaquable(sf::Packet paquet);

        void getJoueurCourant();

        void getJoueursAdverses();

        void parseJoueurCourant(sf::Packet paquet);

        void parseJoueursAdverses(sf::Packet paquet);

        void setDestination(Position p);

        void demanderAttaqueVaisseau(Position p1, Position p2);

        void attaquerVaisseau(sf::Packet paquet);

        void traiterPaquetMasterServeur(void);

        void demanderListeServeurs();

        void getVaisseauxConstructibles();

        void parseVaisseauxConstructibles(sf::Packet paquet);

        void parseListeServeurs(sf::Packet paquet);

    private:

        /// La socket du client
        sf::TcpSocket socket;

        /// La socket du client pour le master serveur
        sf::TcpSocket socketMaster;

        /// Permet de savoir si le réseau est actif (ie. le client est connecté à un serveur)
        bool actif;

        /// Permet de savoir si une partie multi est commencée ou non. Pour qu'une partie soit commencée,  
        /// il faut qu'il y ait deux joueurs de connectés ainsi que le réseau d'activé
        bool partieActive;

        string ip;

        unsigned short port;

        Plateau& plateau;

        Joueur& joueur;
};

#endif
