#ifndef NOEUD_HPP
#define NOEUD_HPP
#include "Point.hpp"

class Noeud{
	public:
		Noeud(Point _point);
		Noeud(Point& _point, int g, Point _parentPoint);
		bool lowerG(const Noeud& noeud);
		bool equal(const Noeud& noeud);
		Point getPoint();
		Point getParentPoint();
		int getG();
	
	private:
		Point point;
		Point parentPoint;
		int distanceG;
};

#endif // NOEUD_HPP
