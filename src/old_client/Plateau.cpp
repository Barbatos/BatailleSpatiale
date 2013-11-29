#include "Plateau.hpp"
#include <iostream>
#include "../commun/enum/TypePaquet.hpp"

Plateau::Plateau() :
    tailleX(0), tailleY(0) {
}

Plateau::~Plateau() {
}

bool Plateau::possedeEvenement(Position p) {
    return cellule[p.x][p.y].possedeEvenement();
}

const DetailEvenement& Plateau::getEvenement(Position p) {
    return cellule[p.x][p.y].getEvenement();
}

bool Plateau::possedeBatiment(Position p) {
    return cellule[p.x][p.y].possedeBatiment();
}

const DetailBatiment& Plateau::getBatiment(Position p) {
    return cellule[p.x][p.y].getBatiment();
}

bool Plateau::possedeVaisseau(Position p) {
    return cellule[p.x][p.y].possedeVaisseau();
}

const DetailVaisseau& Plateau::getVaisseau(Position p) {
    return cellule[p.x][p.y].getVaisseau();
}

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau) {

    paquet >> plateau.tailleX >> plateau.tailleY;

    plateau.cellule.resize(plateau.tailleX, std::vector<Cellule>(plateau.tailleY));

    for (sf::Int16 x = 0 ; x < plateau.tailleX ; ++x)
        for (sf::Int16 y = 0 ; y < plateau.tailleY ; ++y)
            paquet >> plateau.cellule[x][y];

    return paquet;
}

const sf::Int16& Plateau::getTailleX() const {
    return tailleX;
}

const sf::Int16& Plateau::getTailleY() const {
    return tailleY;
}
