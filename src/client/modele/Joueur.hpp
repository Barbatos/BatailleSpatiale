#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include <global.hpp>

/**
 * Classe permettant de stocker les informations des joueurs 
 * qui sont envoyées par le serveur.
 */
class Joueur
{

	public:
		/**
		 * \brief Constructeur par défaut
		 * 
		 * \param _pseudo le pseudo du joueur
		 * \param _ip l'adresse IP du joueur
		 * \param _id l'identifiant du joueur sur le serveur
		 * \param _commandement
		 * \param _requisition
		 * \param _energie
		 * \param _materiaux
		 */
		Joueur(string _pseudo = "Anonymous", string _ip = "",
			sf::Uint16 _id = -1, sf::Int32 _commandement = 0,
			sf::Int32 _requisition = 0, sf::Int32 _energie = 0,
			sf::Int32 _materiaux = 0);

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

		sf::Int32 getCommandement(void);
		sf::Int32 getRequisition(void);
		sf::Int32 getEnergie(void);
		sf::Int32 getMateriaux(void);

	protected:

	private:
		/// Le pseudo du joueur
		string pseudo;

		/// L'adresse IP du joueur
		string ip;

		/// L'identifiant (nombre positif) du joueur sur le serveur
		sf::Uint16 id;

		sf::Int32 commandement;

		sf::Int32 requisition;

		sf::Int32 energie;

		sf::Int32 materiaux;
};

#endif
