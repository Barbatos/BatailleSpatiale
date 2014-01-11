#include "NoeudServeur.hpp"

NoeudServeur::NoeudServeur(Position _position) {
	position = _position;
	distanceG = 0;
	positionParent.setNull();
}

NoeudServeur::NoeudServeur(Position& _position, sf::Int32 g, Position _positionParent) {
	position = _position;
	distanceG = g;
	positionParent = _positionParent;
}

bool NoeudServeur::gInferieur(const NoeudServeur& noeud){
	return distanceG < noeud.distanceG;
}

sf::Int32 NoeudServeur::getG(){
	return distanceG;
}

bool NoeudServeur::operator==(const NoeudServeur& noeud){
	return noeud.position.x == position.x && position.y == noeud.position.y;
}

Position NoeudServeur::getPosition(){
	return position;
}

Position NoeudServeur::getPositionParent(){
	return positionParent;
}
