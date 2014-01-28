#ifndef SERVEURMASTER_HPP
#define SERVEURMASTER_HPP

#include <global.hpp>

class ServeurMaster {

public:
	ServeurMaster();
	int getId();
	sf::Time getDernierHeartbeat();
	sf::TcpSocket* getSocket();
	sf::IpAddress getIp();
	unsigned short getPort();

	void setId(int _id);
	void setDernierHeartbeat(sf::Time dernierHeartbeat);
	void setSocket(sf::TcpSocket* _socket);
	void setIp(sf::IpAddress _ip);
	void setPort(unsigned short _port);

private:
	int id;
	sf::Time dernierHeartbeat;
	sf::TcpSocket* socket;
	sf::IpAddress ip;
	unsigned short port;

};

#endif
