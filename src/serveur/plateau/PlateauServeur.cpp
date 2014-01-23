#include "PlateauServeur.hpp"

PlateauServeur::PlateauServeur(sf::Int32 _tailleX, sf::Int32 _tailleY) :
    tailleX(_tailleX),
    tailleY(_tailleY) {
    cellule.resize(tailleX, std::vector<CelluleServeur>(tailleY));

    for (sf::Int32 x = 0; x < tailleX; ++x)
        for (sf::Int32 y = 0; y < tailleY; ++y)
            cellule[x][y] = CelluleServeur();
}

void PlateauServeur::initialisationTest() {
    cellule[6][4].creerVaisseauTest(TypeVaisseau::Destructeur);
    cellule[5][6].setType(TypeCellule::Inexistant);
    cellule[6][6].setType(TypeCellule::Inexistant);
    cellule[6][5].setType(TypeCellule::Inexistant);
    cellule[4][7].setType(TypeCellule::Inexistant);
    cellule[7][4].setType(TypeCellule::Inexistant);
    cellule[8][3].setType(TypeCellule::Inexistant);
    cellule[0][1].creerBatimentBaseTest();
    (*joueurs)[0].ajouterBatiment(cellule[0][1].getBatiment());
    cellule[8][5].creerVaisseauTest(TypeVaisseau::Leger);
    cellule[7][6].creerVaisseauTest(TypeVaisseau::Constructeur);
    cellule[1][1].creerVaisseauTest();
}

bool PlateauServeur::possedeBatiment(Position p) {
    return cellule[p.x][p.y].possedeBatiment();
}

bool PlateauServeur::possedeVaisseau(Position p) {
    return cellule[p.x][p.y].possedeVaisseau();
}

bool PlateauServeur::possedeEvenement(Position p) {
    return cellule[p.x][p.y].possedeEvenement();
}

VaisseauServeurPtr PlateauServeur::getVaisseau(Position p) {
    return cellule[p.x][p.y].getVaisseau();
}

BatimentServeurPtr PlateauServeur::getBatiment(Position p) {
    return cellule[p.x][p.y].getBatiment();
}

EvenementServeurPtr PlateauServeur::getEvenement(Position p) {
    return cellule[p.x][p.y].getEvenement();
}

int PlateauServeur::getCoutDeplacement(Position p) {
    return cellule[p.x][p.y].getCoutDeplacement();
}

std::list<Position> PlateauServeur::celluleAutour(Position p) {
    std::list<Position> autour;
    Position nouveauPoint;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != j) {
                nouveauPoint.set(p.x + i, p.y + j);
                if (nouveauPoint.x >= 0 && nouveauPoint.y >= 0 && nouveauPoint.x < tailleX && nouveauPoint
                        .y < tailleY)
                    if (celluleAccessible(nouveauPoint))
                        autour.push_back(Position(nouveauPoint));
            }
        }
    }
    return autour;
}

std::list<Position> PlateauServeur::getZoneConstructibleVaisseau(int idJoueur) {
    std::list<Position> zoneConstructible;
    std::list<Position> pointAutour;
    std::list<Position>::iterator p;

    for (sf::Int32 x = 0; x < tailleX; ++x)
        for (sf::Int32 y = 0; y < tailleY; ++y) {
            if(cellule[x][y].possedeBatiment()
                    && cellule[x][y].getBatiment()->getType() == TypeBatiment::Base
                    && cellule[x][y].getBatiment()->getIdJoueur() == idJoueur) {
                pointAutour = celluleAutour(Position(x, y));

                //Pour chaque point autour
                for (p = pointAutour.begin();
                        p != pointAutour.end(); p++) {
                    if(!cellule[p->x][p->y].estAccessible())
                        zoneConstructible.push_back(*p);
                }
            }
        }

    return zoneConstructible;
}

std::list<NoeudServeur> PlateauServeur::getZoneParcourable (
    Position positionVaisseau) {
    //On créé une liste parcourable
    std::list<NoeudServeur> zoneParcourable;

    //On regarde si le vaisseau peut se déplacer
    if (cellule[positionVaisseau.x][positionVaisseau.y].distanceMaximale() > 0) {

        //Liste des noeuds encore à étudier
        std::list<NoeudServeur> openListe;
        std::list<NoeudServeur>::iterator noeudIterateur;

        //Liste des points autour du noeud etudié
        std::list<Position> pointAutour;
        //Le point représentant le noeud etudié
        std::list<Position>::iterator pointCourant;
        bool noeudTrouve = false;

        //On commence par étudier le noeud ou le vaisseau se situe
        NoeudServeur noeudCourant(positionVaisseau);

        //On défini la distance maximale des recherches
        int distanceParcourable = cellule[positionVaisseau.x][positionVaisseau.y]
                                  .distanceMaximale();

        do {

            //On ajoute le noeud courant dans la zoneParcourable
            zoneParcourable.push_back(noeudCourant);

            // on le retire le noeud courant de l'openListe
            for (noeudIterateur = openListe.begin();
                    noeudIterateur != openListe.end(); noeudIterateur++) {
                if (noeudCourant == (*noeudIterateur))
                    noeudIterateur = openListe.erase(noeudIterateur);
            }

            //On recherche les points autour du noeud courant
            pointAutour.clear();
            pointAutour = celluleAutour(noeudCourant.getPosition());

            //Pour chaque point autour
            for (pointCourant = pointAutour.begin();
                    pointCourant != pointAutour.end(); pointCourant++) {

                //Si la cellule est accesible
                if (cellule[pointCourant->x][pointCourant->y].estAccessible()) {

                    //On regarde si il est deja dans l'openliste
                    noeudIterateur = openListe.begin();
                    noeudTrouve = false;
                    while (!noeudTrouve && noeudIterateur != openListe.end()) {
                        if (*pointCourant == (noeudIterateur->getPosition())) {
                            noeudTrouve = true;
                        } else {
                            noeudIterateur++;
                        }
                    }

                    //Si oui alors on le met a jour si le nouveau chemin est meilleur
                    if (noeudTrouve) {
                        if (noeudCourant.getG() + cellule[pointCourant->x][pointCourant
                                ->y].getCoutDeplacement() < noeudIterateur->getG()) {

                            noeudIterateur = openListe.erase(noeudIterateur);
                            openListe.push_back(
                                NoeudServeur(
                                    *pointCourant,
                                    cellule[pointCourant->x][pointCourant
                                                             ->y].getCoutDeplacement(),
                                    noeudCourant.getPosition()));
                        }

                        //Sinon
                    } else {

                        //On regarde si il est dans la zone parcourable(closeList)
                        noeudIterateur = zoneParcourable.begin();
                        while (!noeudTrouve && noeudIterateur != zoneParcourable
                                .end()) {
                            if (*pointCourant == (noeudIterateur->getPosition())) {
                                noeudTrouve = true;
                            } else {
                                noeudIterateur++;
                            }
                        }

                        //Si il n'est ni dans l'openListe ni dans la zone parcourable on l'ajoute à l'openListe
                        if (!noeudTrouve) {
                            openListe.push_back(
                                NoeudServeur(
                                    *pointCourant,
                                    cellule[pointCourant->x][pointCourant
                                                             ->y].getCoutDeplacement() + noeudCourant
                                    .getG(),
                                    noeudCourant.getPosition()));
                        }
                    }
                }
            }

            //Le prochain noeud a étudié est celui qui a la distance G inférieur a tout les autres
            noeudCourant = *(openListe.begin());
            // On prend le noeud avec le G le plus bas
            for (noeudIterateur = openListe.begin();
                    noeudIterateur != openListe.end(); noeudIterateur++) {
                if ((*noeudIterateur).gInferieur(noeudCourant))
                    noeudCourant = *noeudIterateur;
            }

            /*
             * On continue les recherches tant que toute la zone parcourable sur le
             * plateau à été étudié (openListe.empty) ou que la distance du prochain noeud
             * est supérieur a la distance parcourable du vaisseau
             */
        } while (!openListe.empty() && noeudCourant.getG() <= distanceParcourable);
    }
    return zoneParcourable;
}

std::list<Position> PlateauServeur::obtenirChemin(Position p,
        std::list<NoeudServeur> zoneParcourable) {
    //Le chemin à retourner
    std::list<Position> chemin;
    //La position courante à envoyer dans la liste(chemin)
    Position pCourante;
    pCourante.setNull();

    //Booléen pour le while
    bool noeudTrouve;

    //On cherche si la position p est bien dans la zone parcourable
    std::list<NoeudServeur>::iterator noeudIterateur = zoneParcourable.begin();
    while (pCourante.isNull() && noeudIterateur != zoneParcourable.end()) {
        if (p == (noeudIterateur->getPosition())) {
            pCourante = p;
        } else {
            noeudIterateur++;
        }
    }

    //Tant que le chemin n'est pas entierement trouvé
    while (!pCourante.isNull()) {
        noeudTrouve = false;

        //On cherche le noeud qui correspond a la position courante
        std::list<NoeudServeur>::iterator noeudIterateur = zoneParcourable
                .begin();
        while (!noeudTrouve && noeudIterateur != zoneParcourable.end()) {
            if (pCourante == (noeudIterateur->getPosition())) {
                //Si la position parente n'est pas nulle alors ce n'est pas
                //la premiere case donc on ajoute au chemin
                if (!noeudIterateur->getPositionParent().isNull())
                    chemin.push_front(Position(pCourante));

                //On modifie ensuite la position courante
                pCourante = noeudIterateur->getPositionParent();
                noeudTrouve = true;
            } else {
                noeudIterateur++;
            }
        }
    }

    return chemin;
}

bool PlateauServeur::deplacerVaisseau(Position p1, Position p2, std::list<NoeudServeur> zoneParcourable) {
    std::list<NoeudServeur>::iterator noeudIterateur = zoneParcourable.begin();

    if(cellule[p1.x][p1.y].possedeVaisseau() != cellule[p2.x][p2.y].possedeVaisseau()) {
        while (noeudIterateur != zoneParcourable.end()) {
            if (p2 == (noeudIterateur->getPosition())) {
                cellule[p1.x][p1.y].echangerVaisseau(cellule[p2.x][p2.y]);
                return true;
            } else {
                noeudIterateur++;
            }
        }
    }

    return false;
}

bool PlateauServeur::celluleAccessible(Position p) {
    return cellule[p.x][p.y].estAccessible();
}

sf::Int32 PlateauServeur::getTailleX() {
    return tailleX;
}

sf::Int32 PlateauServeur::getTailleY() {
    return tailleY;
}

void PlateauServeur::setJoueurs(std::vector<JoueurServeur> *_joueurs) {
    joueurs = _joueurs;
}

PlateauServeur& PlateauServeur::operator=(const PlateauServeur& plateau2) {
    cellule = plateau2.cellule;

    tailleX = plateau2.tailleX;
    tailleY = plateau2.tailleY;

    return *this;
}

sf::Packet& operator <<(sf::Packet& paquet, const PlateauServeur& plateau) {
    paquet
            << plateau.tailleX
            << plateau.tailleY;

    for (sf::Int32 x = 0; x < plateau.tailleX; ++x)
        for (sf::Int32 y = 0; y < plateau.tailleY; ++y)
            paquet
                    << plateau.cellule[x][y];

    return paquet;
}
