#include "ClientMaster.hpp"

ClientMaster::ClientMaster() : 
	id(-1), socket(NULL), ip(""), port(-1) {

}

int ClientMaster::getId() {
	return id;
}

sf::TcpSocket* ClientMaster::getSocket() {
	return socket;
}

sf::IpAddress ClientMaster::getIp() {
	return ip;
}

unsigned short ClientMaster::getPort() {
	return port;
}

void ClientMaster::setId(int _id) {
	id = _id;
}

void ClientMaster::setSocket(sf::TcpSocket* _socket) {
	socket = _socket;
}

void ClientMaster::setIp(sf::IpAddress _ip) {
	ip = _ip;
}

void ClientMaster::setPort(unsigned short _port) {
	port = _port;
}

