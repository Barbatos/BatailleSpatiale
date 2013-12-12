#ifndef NOEUDSERVEUR_HPP
#define NOEUDSERVEUR_HPP
#include "../../commun/utile/Position.hpp"
#include <SFML/System.hpp>

class NoeudServeur {
	public:
		NoeudServeur(Position _position);
		NoeudServeur(Position& _position, sf::Int16 g, Position _parentPosition);
		bool gInferieur(const NoeudServeur& noeud);
		bool operator==(const NoeudServeur& noeud);
		Position getPosition();
		Position getPositionParent();
		sf::Int16 getG();
	
	private:
		Position position;
		Position positionParent;
		sf::Int16 distanceG;
};

#endif // NOEUDSERVEUR_HPP
