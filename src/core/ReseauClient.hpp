#ifndef _RESEAU_CLIENT_H_
#define _RESEAU_CLIENT_H_

#include "../global.hpp"

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
		 * \param ip l'ip du serveur sur lequel on veut se connecter
		 * \param port le port du serveur
		 */
		ReseauClient(string ip, unsigned short port);

		/**
		 * \brief Destructeur par défaut
		 */
		~ReseauClient(void);
		
		/**
		 * \brief Traite un paquet reçu de la part du serveur
		 *
		 * \param paquet le paquet reçu
		 */
		void TraiterPaquetServeur(sf::Packet& paquet);

	private:

		/// La socket du client
		sf::TcpSocket socket;
};

#endif
