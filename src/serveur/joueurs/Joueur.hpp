#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include "../../global.hpp"

/**
 * Classe permettant de gérer les joueurs.
 */
class Joueur {
	public:
		/**
		 * \brief Constructeur par défaut
		 * 
		 */
		Joueur(void);

		/**
		 * \brief Récupération de la socket réseau du joueur
		 * 
		 * \return un pointeur vers la socket de type sf::TcpSocket
		 */
		sf::TcpSocket* getSocket(void);

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

		/**
		 * \brief 
		 * 
		 */
		sf::Int16 getCommandement(void);
		sf::Int16 getRequisition(void);
		sf::Int32 getEnergie(void);
		sf::Int32 getMateriaux(void);

		/// Setters
		void setSocket(sf::TcpSocket* _socket);
		void setPseudo(string _pseudo);
		void setIp(string _ip);
		void setId(sf::Uint16 _id);
		void setCommandement(sf::Int16 _commandement);
		void setRequisition(sf::Int16 _requisition);
		void setEnergie(sf::Int32 _energie);
		void setMateriaux(sf::Int32 _materiaux);
	protected:

	private:
		/// La socket du joueur
		sf::TcpSocket* socket;

		/// Le pseudo du joueur
		string pseudo;

		/// L'adresse IP du joueur
		string ip;

		/// L'identifiant (nombre positif) du joueur sur le serveur
		sf::Uint16 id;

		sf::Int16 commandement;

		sf::Int16 requisition;

		sf::Int32 energie;

		sf::Int32 materiaux;
};

#endif
