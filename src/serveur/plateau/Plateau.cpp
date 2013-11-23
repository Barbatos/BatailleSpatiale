#include "Plateau.hpp"

Plateau::Plateau(sf::Int16 _tailleX, sf::Int16 _tailleY) :
    tailleX(_tailleX), tailleY(_tailleY) {

    cellule.resize(tailleX, std::vector<Cellule>(tailleY));

    for (sf::Int16 x = 0 ; x < tailleX ; ++x)
        for (sf::Int16 y = 0 ; y < tailleY ; ++y)
            cellule[x][y] = Cellule();
}

bool Plateau::possedeBatiment(Position p) {
    return cellule[p.x][p.y].possedeBatiment();
}

bool Plateau::possedeVaisseau(Position p) {
    return cellule[p.x][p.y].possedeVaisseau();
}

bool Plateau::possedeEvenement(Position p) {
    return cellule[p.x][p.y].possedeEvenement();
}

VaisseauPtr Plateau::getVaisseau(Position p) {
    return cellule[p.x][p.y].getVaisseau();
}

BatimentPtr Plateau::getBatiment(Position p) {
    return cellule[p.x][p.y].getBatiment();
}

EvenementPtr Plateau::getEvenement(Position p) {
    return cellule[p.x][p.y].getEvenement();
}

int Plateau::getCoutDeplacement(Position p) {
    return cellule[p.x][p.y].getCoutDeplacement();
}

std::list<Position> Plateau::celluleAutour(Position p) {
    std::list<Position> autour;
    Position nouveauPoint;
    for(int i =-1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i != j) {
                nouveauPoint.set(p.x + i, p.y + j);
                if(nouveauPoint.x >= 0 && nouveauPoint.y >= 0 &&
                        nouveauPoint.x < tailleX && nouveauPoint.y < tailleY)
                    if(celluleAccessible(nouveauPoint))
                        autour.push_back(Position(nouveauPoint));

            }
        }
    }
    return autour;
}

bool Plateau::celluleAccessible(Position p) {
    return cellule[p.x][p.y].estAccessible();
}

sf::Int16 Plateau::getTailleX() {
    return tailleX;
}

sf::Int16 Plateau::getTailleY() {
    return tailleY;
}
