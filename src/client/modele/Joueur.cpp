#include "Joueur.hpp"

Joueur::Joueur(string _pseudo, string _ip, sf::Uint16 _id) : pseudo(_pseudo), ip(_ip), id(_id){

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
