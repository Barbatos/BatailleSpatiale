#include "Joueur.hpp"

Joueur::Joueur(void) : socket(NULL), pseudo("Anonymous"), ip(""), id(-1){

}

sf::TcpSocket* Joueur::getSocket(void){
	return this->socket;
}

string Joueur::getPseudo(void){
	return this->pseudo;
}

string Joueur::getIp(void){
	return this->ip;
}

sf::Uint16 Joueur::getId(void){
	return this->id;
}

void Joueur::setSocket(sf::TcpSocket* _socket){
	this->socket = _socket;
}

void Joueur::setPseudo(string _pseudo){
	this->pseudo = _pseudo;
}

void Joueur::setIp(string _ip){
	this->ip = _ip;
}

void Joueur::setId(sf::Uint16 _id){
	this->id = _id;
}
