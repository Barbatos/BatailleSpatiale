#include "Noeud.hpp"

Noeud::Noeud(Position _position) {
	position = _position;
	distanceG = 0;
	positionParent.setNull();
}

Noeud::Noeud(Position& _position, sf::Int16 g, Position _positionParent) {
	position = _position;
	distanceG = g;
	positionParent = _positionParent;
}

bool Noeud::gInferieur(const Noeud& noeud){
	return distanceG < noeud.distanceG;
}

sf::Int16 Noeud::getG(){
	return distanceG;
}

bool Noeud::operator==(const Noeud& noeud){
	return noeud.position.x == position.x && position.y == noeud.position.y;
}

Position Noeud::getPosition(){
	return position;
}

Position Noeud::getPositionParent(){
	return positionParent;
}
