#ifndef NOEUD_HPP
#define NOEUD_HPP
#include "../../commun/utile/Position.hpp"
#include <SFML/System.hpp>

class Noeud {
	public:
		Noeud(Position _position);
		Noeud(Position& _position, sf::Int16 g, Position _parentPosition);
		bool gInferieur(const Noeud& noeud);
		bool operator==(const Noeud& noeud);
		Position getPosition();
		Position getPositionParent();
		sf::Int16 getG();
	
	private:
		Position position;
		Position positionParent;
		sf::Int16 distanceG;
};

#endif // NOEUD_HPP
