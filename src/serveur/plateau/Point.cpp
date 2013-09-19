#include "Point.hpp"

Point::Point(int _x, int _y) : x(_x), y(_y) {

}

Point::Point(const Point& point) : x(point.x), y(point.y) {

}

bool Point::estEgal(const Point& point) const {
	return x == point.x && y == point.y;
}

void Point::set(const Point& point) {
	x = point.x;
	y = point.y;
}
