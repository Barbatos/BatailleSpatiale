#ifndef CLIENTMASTER_HPP
#define CLIENTMASTER_HPP

#include <global.hpp>

class ClientMaster {

public:
    ClientMaster();
    int getId();
    sf::TcpSocket* getSocket();
    sf::IpAddress getIp();
    unsigned short getPort();

    void setId(int _id);
    void setSocket(sf::TcpSocket* _socket);
    void setIp(sf::IpAddress _ip);
    void setPort(unsigned short _port);

private:
    int id;
    sf::TcpSocket* socket;
    sf::IpAddress ip;
    unsigned short port;

};

#endif
