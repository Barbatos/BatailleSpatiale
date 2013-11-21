#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include <global.hpp>

/**
 * Classe permettant de stocker les informations des joueurs 
 * qui sont envoyées par le serveur.
 */
class Joueur {

	public:
		/**
		 * \brief Constructeur par défaut
		 * 
		 * \param _pseudo le pseudo du joueur
		 * \param _ip l'adresse IP du joueur
		 * \param _id l'identifiant du joueur sur le serveur
		 */
		Joueur(string _pseudo = "Anonymous", string _ip = "", sf::Uint16 _id = -1);

		/**
		 * \brief Récupération du pseudo du joueur
		 * 
		 * \return le pseudo sous forme de chaîne de caractères
		 */
		string getPseudo(void);

		/**
		 * \brief Récupération de l'adresse IP du joueur
		 * 
		 * \return l'adresse ip sous forme de chaîne de caractères
		 */
		string getIp(void);

		/**
		 * \brief Récupération du numéro du joueur sur le serveur
		 * 
		 * \return Le numéro du joueur
		 */
		sf::Uint16 getId(void);

	protected:

	private:
		/// Le pseudo du joueur
		string pseudo;

		/// L'adresse IP du joueur
		string ip;

		/// L'identifiant (nombre positif) du joueur sur le serveur
		sf::Uint16 id;
};

#endif
