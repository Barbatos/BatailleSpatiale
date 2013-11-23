#include "Plateau.hpp"

Plateau::Plateau(sf::Int16 _tailleX, sf::Int16 _tailleY) :
    tailleX(_tailleX), tailleY(_tailleY) {

    cellule.resize(tailleX, std::vector<Cellule>(tailleY));

    for (sf::Int32 x = 0 ; x < tailleX ; ++x)
        for (sf::Int32 y = 0 ; y < tailleY ; ++y)
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

sf::Int16 Plateau::getTailleX() {
    return tailleX;
}

sf::Int16 Plateau::getTailleY() {
    return tailleY;
}
