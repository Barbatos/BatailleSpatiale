#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include "../../global.hpp"

class Joueur {
	public:
		Joueur(void);
		sf::TcpSocket* getSocket(void);
		string getPseudo(void);
		string getIp(void);
		sf::Uint16 getId(void);

		void setSocket(sf::TcpSocket* _socket);
		void setPseudo(string _pseudo);
		void setIp(string _ip);
		void setId(sf::Uint16 _id);
	protected:

	private:
		sf::TcpSocket* socket;
		string pseudo;
		string ip;
		sf::Uint16 id;
};

#endif
