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

std::list<Noeud> Plateau::getZoneParcourable(Position positionVaisseau) {
    //On créé une liste parcourable
    std::list<Noeud> zoneParcourable;
    
    //On regarde si le vaisseau peut se déplacer
    if(cellule[positionVaisseau.x][positionVaisseau.y].distanceMaximale() > 0) {

        std::list<Noeud> openListe;
        std::list<Noeud>::iterator noeudIterateur;

        std::list<Position> pointAutour;
        std::list<Position>::iterator pointCourant;
        bool noeudTrouve = false;

        Noeud noeudCourant(positionVaisseau);
        int distanceParcourable = cellule[positionVaisseau.x][positionVaisseau.y].distanceMaximale();
        
        do {

            zoneParcourable.push_back(noeudCourant);

            // on le retire de l'openListe
            for(noeudIterateur = openListe.begin(); noeudIterateur != openListe.end(); noeudIterateur++) {
                if(noeudCourant.equal(*noeudIterateur))
                    noeudIterateur = openListe.erase(noeudIterateur);
            }

            pointAutour.clear();
            pointAutour = celluleAutour(noeudCourant.getPosition());

            for(pointCourant = pointAutour.begin(); pointCourant != pointAutour.end(); pointCourant++) {

                if(cellule[pointCourant->x][pointCourant->y].estAccessible()) {

                    noeudIterateur = openListe.begin();
                    noeudTrouve = false;
                    while(!noeudTrouve && noeudIterateur != openListe.end()) {
                        if(*pointCourant == (noeudIterateur->getPosition())) {
                            noeudTrouve = true;
                        } else {
                            noeudIterateur++;
                        }
                    }
                    if (noeudTrouve) {
                        if (noeudCourant.getG() + cellule[pointCourant->x][pointCourant->y].getCoutDeplacement() < noeudIterateur->getG()) {

                            noeudIterateur = openListe.erase(noeudIterateur);
                            openListe.push_back(Noeud(*pointCourant, cellule[pointCourant->x][pointCourant->y].getCoutDeplacement(), noeudCourant.getPosition()));
                        }


                    } else {

                        noeudIterateur = zoneParcourable.begin();
                        noeudTrouve = false;
                        while(!noeudTrouve && noeudIterateur != zoneParcourable.end()) {
                            if(*pointCourant == (noeudIterateur->getPosition())) {
                                noeudTrouve = true;
                            } else {
                                noeudIterateur++;
                            }
                        }
                        if (!noeudTrouve) {
                            openListe.push_back(Noeud(*pointCourant, cellule[pointCourant->x][pointCourant->y].getCoutDeplacement() + noeudCourant.getG(), noeudCourant.getPosition()));
                        }
                    }
                }
            }

            noeudCourant = *(openListe.begin());
            // On prend le noeud avec le G le plus bas
            for(noeudIterateur = openListe.begin(); noeudIterateur != openListe.end(); noeudIterateur++) {
                if ((*noeudIterateur).lowerG(noeudCourant))
                    noeudCourant = *noeudIterateur;
            }

        } while(!openListe.empty() && noeudCourant.getG() <= distanceParcourable);
    }
    return zoneParcourable;
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
