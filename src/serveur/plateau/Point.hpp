#ifndef POINT_HPP
#define POINT_HPP

class Point{
	public:
		Point(int _x=0, int _y=0);
		Point(const Point& point);
		void set(const Point& point);
		bool estEgal(const Point& point) const;
		int x;
		int y;
};

#endif // POINT_HPP
