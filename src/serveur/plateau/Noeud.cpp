#include "Noeud.hpp"

Noeud::Noeud(Point _point) {
	point = _point;
	distanceG = 0;
	parentPoint = Point(-1, -1);
}

Noeud::Noeud(Point& _point, int g, Point _parentPoint) {
	point = _point;
	distanceG = g;
	parentPoint = _parentPoint;
}

bool Noeud::lowerG(const Noeud& noeud){
	return distanceG < noeud.distanceG;
}

int Noeud::getG(){
	return distanceG;
}

bool Noeud::equal(const Noeud& noeud){
	return noeud.point.x == point.x && point.y == noeud.point.y;
}

Point Noeud::getPoint(){
	return point;
}

Point Noeud::getParentPoint(){
	return parentPoint;
}
