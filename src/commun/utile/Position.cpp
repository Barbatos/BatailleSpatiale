#include "Position.hpp"

Position::Position(int _x, int _y) :
    x(_x), y(_y) {

}

bool Position::operator==(Position& p) {
    return x == p.x && y == p.y;
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
