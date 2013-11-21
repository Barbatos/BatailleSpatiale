#include "Joueur.hpp"

Joueur::Joueur(void) : socket(NULL), pseudo("Anonymous"), ip(""), id(-1), commandement(0), requisition(0), energie(0), materiaux(0) {

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

sf::Int16 Joueur::getCommandement(void){
	return this->commandement;
}

sf::Int16 Joueur::getRequisition(void){
	return this->requisition;
}

sf::Int32 Joueur::getEnergie(void){
	return this->energie;
}

sf::Int32 Joueur::getMateriaux(void){
	return this->materiaux;
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

void Joueur::setCommandement(sf::Int16 _commandement){
	this->commandement = _commandement;
}

void Joueur::setRequisition(sf::Int16 _requisition){
	this->requisition = _requisition;
}

void Joueur::setEnergie(sf::Int32 _energie){
	this->energie = _energie;
}

void Joueur::setMateriaux(sf::Int32 _materiaux){
	this->materiaux = _materiaux;
}
