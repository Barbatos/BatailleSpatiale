#include "Plateau.hpp"

Plateau::Plateau(sf::Int32 _tailleX, sf::Int32 _tailleY) :
    tailleX(_tailleX), tailleY(_tailleY) {

    cellule.resize(tailleX, std::vector<Cellule>(tailleY));

    for (sf::Int32 x = 0 ; x < tailleX ; ++x)
        for (sf::Int32 y = 0 ; y < tailleY ; ++y)
            cellule[x][y] = Cellule();
}
