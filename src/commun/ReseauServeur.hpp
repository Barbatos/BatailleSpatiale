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
class ReseauServeur
{

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
		void EcouterReseau(void);

		/**
		 * \brief Fonction permettant de traiter un paquet reçu d'un client
		 * en fonction du type de paquet.
		 * 
		 * \param typePaquet le type de paquet reçu
		 * \param msg le contenu du paquet
		 */
		void TraiterPaquetClient(JoueurServeur& joueur, sf::Uint16 typePaquet, string& msg);

		/**
		 * \brief Fonction traitant une commande client commençant par un tiret /
		 * 
		 * \param joueur le joueur ayant effectué la commande
		 * \param commande la commande envoyée par le joueur
		 */
		void TraiterCommandeClient(JoueurServeur& joueur, string& commande);

		/**
		 * \brief Envoi d'un message par le serveur à tous les clients
		 * 
		 * \param message le message à envoyer
		 */
		void EnvoiATous(string& message);

		/**
		 * \brief Envoi d'un message par le serveur à un unique client
		 * 
		 * \param client la socket du client
		 * \param message le message à envoyer
		 */
		void EnvoiUnique(sf::TcpSocket& client, string& message);

		/**
		 * \brief Envoi du plateau à un client
		 * 
		 * \param client la socket du client
		 * \param plateau le plateau
		 */
		void EnvoiPlateau(sf::TcpSocket& client, PlateauServeur& _plateau);

		void setPlateau(PlateauServeur& plateau);

		void threadReseau();

		void lancerReseau();

		void fermerReseau();

		void EnvoiZoneParcourable(sf::TcpSocket& client, sf::Int32 tailleZone, std::list<NoeudServeur> noeuds);

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

