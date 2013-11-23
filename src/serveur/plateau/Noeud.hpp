#ifndef NOEUD_HPP
#define NOEUD_HPP
#include "../../commun/utile/Position.hpp"

class Noeud {
	public:
		Noeud(Position _position);
		Noeud(Position& _position, int g, Position _parentPosition);
		bool lowerG(const Noeud& noeud);
		bool equal(const Noeud& noeud);
		Position getPosition();
		Position getParentPosition();
		int getG();
	
	private:
		Position position;
		Position parentPosition;
		int distanceG;
};

#endif // NOEUD_HPP
