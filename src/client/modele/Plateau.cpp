#include "Plateau.hpp"

Plateau::Plateau()
                : tailleX(0), tailleY(0) {
}

bool Plateau::possedeEvenement(Position p) {
    return positionValide(p) && cellule[p.x][p.y].possedeEvenement();
}

const DetailEvenement& Plateau::getEvenement(Position p) {
    return cellule[p.x][p.y].getEvenement();
}

bool Plateau::possedeBatiment(Position p) {
    return positionValide(p) && cellule[p.x][p.y].possedeBatiment();
}

const DetailBatiment& Plateau::getBatiment(Position p) {
    return cellule[p.x][p.y].getBatiment();
}

bool Plateau::possedeVaisseau(Position p) {
    return positionValide(p) && cellule[p.x][p.y].possedeVaisseau();
}

const DetailVaisseau& Plateau::getVaisseau(Position p) {
    return cellule[p.x][p.y].getVaisseau();
}

const sf::Int32& Plateau::getTailleX() const {
    return tailleX;
}

const sf::Int32& Plateau::getTailleY() const {
    return tailleY;
}

bool Plateau::positionValide(Position p) {
    return p.x < tailleX && p.y < tailleY;
}

const Cellule& Plateau::getCellule(Position p) {
    return cellule[p.x][p.y];
}

void Plateau::viderZoneParcourable() {
    for (std::vector<std::vector<Cellule>>::size_type i = 0; i < cellule.size(); i++)
        for (std::vector<Cellule>::size_type j = 0; j < cellule[i].size(); j++)
            cellule[i][j].setParcourable(false);
}

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau) {

    paquet >> plateau.tailleX >> plateau.tailleY;

    plateau.cellule.resize(plateau.tailleX, std::vector<Cellule>(plateau.tailleY));

    for (sf::Int32 x = 0; x < plateau.tailleX; ++x)
        for (sf::Int32 y = 0; y < plateau.tailleY; ++y)
            paquet >> plateau.cellule[x][y];

    return paquet;
}
