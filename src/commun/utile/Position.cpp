#include "Position.hpp"
Position::Position(sf::Int32 _x, sf::Int32 _y) :
	x(_x),
	y(_y) {
}
bool Position::operator==(Position p) const {
	return x == p.x && y == p.y;
}
bool Position::operator!=(Position p) const {
	return x != p.x || y != p.y;
}
bool Position::isNull() const {
	return x == -32768 && y == -32768;
}
void Position::operator+=(Position& p) {
	x += p.x;
	y += p.y;
}
void Position::operator-=(Position& p) {
	x -= p.x;
	y -= p.y;
}
Position operator+(Position& p1, Position& p2) {
	Position p(p1.x, p1.y);
	p += p2;
	return p;
}
Position operator-(Position& p1, Position& p2) {
	Position p(p1.x, p1.y);
	p -= p2;
	return p;
}
void Position::operator=(Position p) {
	set(p.x, p.y);
}
void Position::set(sf::Int32 _x, sf::Int32 _y) {
	x = _x;
	y = _y;
}
void Position::setNull() {
	x = -32768;
	y = -32768;
}
sf::Packet& operator <<(sf::Packet& paquet, const Position& pos) {
	paquet << pos.x << pos.y;
	return paquet;
}
sf::Packet& operator >>(sf::Packet& paquet, Position& pos) {
	paquet >> pos.x >> pos.y;
	return paquet;
}
