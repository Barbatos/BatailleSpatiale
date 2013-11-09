#ifndef _RESEAU_GLOBAL_H_
#define _RESEAU_GLOBAL_H_

#include "../global.hpp"

/**
 * Classe réseau qui contient les fonctions utilisables 
 * à la fois par le client et le serveur.
 */
class ReseauGlobal
{

	public:

		/**
		 * \brief Fonction permettant de recevoir un paquet réseau
		 * 
		 * \param socket la socket de la machine réceptrice du paquet
		 * \param paquet le paquet reçu
		 * \param timeout temps maximal de récupération du paquet, par défaut 0 secondes
		 */
		static bool ReceptionPaquet(sf::TcpSocket& socket, sf::Packet& paquet, sf::Time timeout = sf::seconds(0.0f));

		/**
		 * \brief Fonction permettant d'envoyer un paquet réseau
		 * 
		 * \param socket la socket de la machine émettrice du paquet
		 * \param paquet le paquet envoyé
		 */
		static void EnvoiPaquet(sf::TcpSocket& socket, sf::Packet& paquet);
};

#endif
