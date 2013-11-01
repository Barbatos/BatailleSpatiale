#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include "../../global.hpp"

class Joueur {
	public:
		Joueur(void);
		sf::TcpSocket* getSocket(void);
		string getPseudo(void);
		string getIp(void);
		int getId(void);

		void setSocket(sf::TcpSocket* _socket);
		void setPseudo(string _pseudo);
		void setIp(string _ip);
		void setId(int _id);
	protected:

	private:
		sf::TcpSocket* socket;
		string pseudo;
		string ip;
		int id;
};

#endif
