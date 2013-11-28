#ifndef _RESEAU_CLIENT_H_
#define _RESEAU_CLIENT_H_

#include "../global.hpp"
#include "ReseauGlobal.hpp"
#include "enum/TypePaquet.hpp"

/**
 * Classe qui permet à un client de se connecter à
 * un serveur de jeu et d'envoyer/recevoir des infos.
 */
class ReseauClient
{

	public:
		/**
		 * \brief Constructeur par défaut
		 * 
		 */
		ReseauClient(void);

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

		sf::TcpSocket& getSocket(void);

		void EnvoyerPseudoServeur(string pseudo);

	private:

		/// La socket du client
		sf::TcpSocket socket;

		/// Permet de savoir si le réseau est actif (ie. le client est connecté à un serveur)
		bool actif;
};

#endif
