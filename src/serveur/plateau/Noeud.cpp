#include "Noeud.hpp"

Noeud::Noeud(Position _position) {
	position = _position;
	distanceG = 0;
	parentPosition = Position(-1, -1);
}

Noeud::Noeud(Position& _position, int g, Position _parentPosition) {
	position = _position;
	distanceG = g;
	parentPosition = _parentPosition;
}

bool Noeud::lowerG(const Noeud& noeud){
	return distanceG < noeud.distanceG;
}

int Noeud::getG(){
	return distanceG;
}

bool Noeud::equal(const Noeud& noeud){
	return noeud.position.x == position.x && position.y == noeud.position.y;
}

Position Noeud::getPosition(){
	return position;
}

Position Noeud::getParentPosition(){
	return parentPosition;
}
