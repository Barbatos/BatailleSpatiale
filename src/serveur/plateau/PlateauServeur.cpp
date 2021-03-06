#include "PlateauServeur.hpp"
#include "../structures/vaisseaux/constructeurs/Constructeur.hpp"

PlateauServeur::PlateauServeur(sf::Int32 _tailleX, sf::Int32 _tailleY) :
    joueurs(nullptr),
    tailleX(_tailleX),
    tailleY(_tailleY) {
    cellule.resize(tailleX, std::vector<CelluleServeur>(tailleY));

    for (sf::Int32 x = 0; x < tailleX; ++x)
        for (sf::Int32 y = 0; y < tailleY; ++y)
            cellule[x][y] = CelluleServeur();
}

void PlateauServeur::initialisationTest() {
    cellule[5][6].setType(TypeCellule::Inexistant);
    cellule[6][6].setType(TypeCellule::Inexistant);
    cellule[6][5].setType(TypeCellule::Inexistant);
    cellule[4][7].setType(TypeCellule::Inexistant);
    cellule[7][4].setType(TypeCellule::Inexistant);
    cellule[20-5][20-6].setType(TypeCellule::Inexistant);
    cellule[20-6][20-6].setType(TypeCellule::Inexistant);
    cellule[20-6][20-5].setType(TypeCellule::Inexistant);
    cellule[20-4][20-7].setType(TypeCellule::Inexistant);
    cellule[20-7][20-4].setType(TypeCellule::Inexistant);
    cellule[15][17].setType(TypeCellule::Inexistant);
    cellule[14][12].setType(TypeCellule::Inexistant);
    cellule[17][9].setType(TypeCellule::Inexistant);
    cellule[12][11].setType(TypeCellule::Inexistant);
    cellule[8][14].setType(TypeCellule::Inexistant);
    cellule[8][8].setType(TypeCellule::Inexistant);
    cellule[9][9].setType(TypeCellule::Inexistant);
    cellule[10][10].setType(TypeCellule::Inexistant);
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

std::list<Position> PlateauServeur::celluleAutour(Position p, bool videTolere) {
    std::list<Position> autour;
    Position nouveauPoint;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != j) {
                nouveauPoint.set(p.x + i, p.y + j);
                if (nouveauPoint.x >= 0 && nouveauPoint.y >= 0 && nouveauPoint.x < tailleX && nouveauPoint
                        .y < tailleY)
                    if (videTolere || celluleAccessible(nouveauPoint))
                        autour.push_back(Position(nouveauPoint));
            }
        }
    }
    return autour;
}

std::list<Position> PlateauServeur::getZoneConstructibleBatiment(Position position, sf::Int32 idJoueur) {
    std::list<Position> zoneConstructible;
    std::list<Position> pointAutour;
    std::list<Position>::iterator p;

    if(cellule[position.x][position.y].possedeVaisseau()
            && cellule[position.x][position.y].getVaisseau()->getType() == TypeVaisseau::Constructeur
            && cellule[position.x][position.y].getVaisseau()->getIdJoueur() == idJoueur)
        pointAutour = celluleAutour(position);

    //Pour chaque point autour
    for (p = pointAutour.begin();
            p != pointAutour.end(); p++) {
        zoneConstructible.push_back(*p);
    }

    return zoneConstructible;
}

std::list<Position> PlateauServeur::getZoneConstructibleVaisseau(sf::Int32 idJoueur) {
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
                    zoneConstructible.push_back(*p);
                }
            }
        }

    return zoneConstructible;
}

Position PlateauServeur::getVaisseauConstructeur(sf::Int32 idJoueur) {
    Position p = Position(-1, -1);

    for (sf::Int32 x = 0; x < tailleX; ++x) {
        for (sf::Int32 y = 0; y < tailleY; ++y) {
            if(cellule[x][y].possedeVaisseau()
                && cellule[x][y].getVaisseau()->getType() == TypeVaisseau::Constructeur
                && cellule[x][y].getVaisseau()->getIdJoueur() == idJoueur) {
                p = Position(x, y);
                return p;
            }
        }
    }
    return p;
}

std::list<Position> PlateauServeur::getVaisseauxAttaque(sf::Int32 idJoueur) {
    std::list<Position> listeVaisseaux;

    for (sf::Int32 x = 0; x < tailleX; ++x) {
        for (sf::Int32 y = 0; y < tailleY; ++y) {
            if(cellule[x][y].possedeVaisseau() 
                && ((cellule[x][y].getVaisseau()->getType() == TypeVaisseau::Chasseur) || (cellule[x][y].getVaisseau()->getType() == TypeVaisseau::Croiseur))
                && (cellule[x][y].getVaisseau()->getIdJoueur() == idJoueur)) {
                listeVaisseaux.push_back(Position(x, y));
            }
        }
    }

    return listeVaisseaux;
}

std::list<Position> PlateauServeur::getStructuresEnnemies(sf::Int32 idJoueur) {
    std::list<Position> listeStructures;

    for (sf::Int32 x = 0; x < tailleX; ++x) {
        for (sf::Int32 y = 0; y < tailleY; ++y) {
            if( (cellule[x][y].possedeVaisseau() && (cellule[x][y].getVaisseau()->getIdJoueur() != idJoueur))
                ||  (cellule[x][y].possedeBatiment() && (cellule[x][y].getBatiment()->getIdJoueur() != idJoueur)) ) {
                listeStructures.push_back(Position(x, y));
            }
        }
    }

    return listeStructures;
}

std::list<Position> PlateauServeur::getStructuresAttaquables(sf::Int32 idJoueur, std::list<NoeudServeur>& listeNoeuds) {
    std::list<Position> structuresEnnemies;
    std::list<Position> structuresAttaquables;
    std::list<NoeudServeur>::iterator noeudIterator;
    std::list<Position>::iterator posIterator;

    structuresEnnemies = getStructuresEnnemies(idJoueur);

    for (noeudIterator = listeNoeuds.begin(); noeudIterator != listeNoeuds.end(); noeudIterator++) {
        for (posIterator = structuresEnnemies.begin(); posIterator != structuresEnnemies.end(); posIterator++) {
            if(noeudIterator->getPosition() == *posIterator) {
                structuresAttaquables.push_back(*posIterator);
            }
        }
    }

    return structuresAttaquables;
}

void PlateauServeur::getZoneVisiblePosition (
    std::list<NoeudServeur>& zoneVisible, Position p) {
    //On créé une liste attaquable
    std::list<NoeudServeur>::iterator noeudIterateur;

    //On regarde si le batiment ou le vaisseau peut attaquer
    if (cellule[p.x][p.y].attaqueMaximale() > 0) {

        //Liste des noeuds encore à étudier
        std::list<NoeudServeur> openListe;

        //Liste des points autour du noeud etudié
        std::list<Position> pointAutour;
        //Le point représentant le noeud etudié
        std::list<Position>::iterator pointCourant;
        bool noeudTrouve = false;

        //On commence par étudier le noeud ou le vaisseau se situe
        NoeudServeur noeudCourant(p);

        //On défini la distance maximale des recherches
        int distanceVisible = cellule[p.x][p.y].visibiliteMaximale();

        do {

            //On ajoute le noeud courant dans la zoneParcourable
            zoneVisible.push_back(noeudCourant);

            // on le retire le noeud courant de l'openListe
            for (noeudIterateur = openListe.begin();
                    noeudIterateur != openListe.end(); noeudIterateur++) {
                if (noeudCourant == (*noeudIterateur))
                    noeudIterateur = openListe.erase(noeudIterateur);
            }

            //On recherche les points autour du noeud courant
            pointAutour.clear();
            pointAutour = celluleAutour(noeudCourant.getPosition(), true);

            //Pour chaque point autour
            for (pointCourant = pointAutour.begin();
                    pointCourant != pointAutour.end(); pointCourant++) {


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
                    if (noeudCourant.getG() + 1 < noeudIterateur->getG()) {

                        noeudIterateur = openListe.erase(noeudIterateur);
                        openListe.push_back(
                            NoeudServeur(
                                *pointCourant, 1,
                                noeudCourant.getPosition()));
                    }

                    //Sinon
                } else {

                    //On regarde si il est dans la zone attaquable(closeList)
                    noeudIterateur = zoneVisible.begin();
                    while (!noeudTrouve && noeudIterateur != zoneVisible
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
                                *pointCourant,1 + noeudCourant.getG(),
                                noeudCourant.getPosition()));
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
        } while (!openListe.empty() && noeudCourant.getG() <= distanceVisible);
    }
}

std::list<NoeudServeur> PlateauServeur::getZoneVisible (sf::Int32 idJoueur) {
    std::list<NoeudServeur> zoneVisible;

    for (sf::Int32 x = 0; x < tailleX; ++x)
        for (sf::Int32 y = 0; y < tailleY; ++y) {
            if(cellule[x][y].getIdJoueur() == idJoueur) {
                getZoneVisiblePosition(zoneVisible, Position(x,y));
            }
        }

    return zoneVisible;
}

std::list<NoeudServeur> PlateauServeur::getZoneAttaquable (
    Position p) {
    //On créé une liste attaquable
    std::list<NoeudServeur> zoneAttaquable;
    std::list<NoeudServeur>::iterator noeudIterateur;
    sf::Int32 idJoueur = cellule[p.x][p.y].getIdJoueur();

    //On regarde si le batiment ou le vaisseau peut attaquer
    if (cellule[p.x][p.y].attaqueMaximale() > 0) {

        //Liste des noeuds encore à étudier
        std::list<NoeudServeur> openListe;

        //Liste des points autour du noeud etudié
        std::list<Position> pointAutour;
        //Le point représentant le noeud etudié
        std::list<Position>::iterator pointCourant;
        bool noeudTrouve = false;

        //On commence par étudier le noeud ou le vaisseau se situe
        NoeudServeur noeudCourant(p);

        //On défini la distance maximale des recherches
        int distanceAttaquable = cellule[p.x][p.y]
                                 .attaqueMaximale();

        do {

            //On ajoute le noeud courant dans la zoneParcourable
            zoneAttaquable.push_back(noeudCourant);

            // on le retire le noeud courant de l'openListe
            for (noeudIterateur = openListe.begin();
                    noeudIterateur != openListe.end(); noeudIterateur++) {
                if (noeudCourant == (*noeudIterateur))
                    noeudIterateur = openListe.erase(noeudIterateur);
            }

            //On recherche les points autour du noeud courant
            pointAutour.clear();
            pointAutour = celluleAutour(noeudCourant.getPosition(), true);

            //Pour chaque point autour
            for (pointCourant = pointAutour.begin();
                    pointCourant != pointAutour.end(); pointCourant++) {


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
                    if (noeudCourant.getG() + 1 < noeudIterateur->getG()) {

                        noeudIterateur = openListe.erase(noeudIterateur);
                        openListe.push_back(
                            NoeudServeur(
                                *pointCourant, 1,
                                noeudCourant.getPosition()));
                    }

                    //Sinon
                } else {

                    //On regarde si il est dans la zone attaquable(closeList)
                    noeudIterateur = zoneAttaquable.begin();
                    while (!noeudTrouve && noeudIterateur != zoneAttaquable
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
                                *pointCourant,1 + noeudCourant.getG(),
                                noeudCourant.getPosition()));
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
        } while (!openListe.empty() && noeudCourant.getG() <= distanceAttaquable);

        for (noeudIterateur = zoneAttaquable.begin();
                noeudIterateur != zoneAttaquable.end(); noeudIterateur++) {
            Position pos = noeudIterateur->getPosition();
            if(cellule[pos.x][pos.y].getIdJoueur() == idJoueur)
                noeudIterateur = openListe.erase(noeudIterateur);
        }
    }

    return zoneAttaquable;
}

std::list<NoeudServeur> PlateauServeur::getZoneParcourable (
    Position positionVaisseau, sf::Int32 energie) {
    //On créé une liste parcourable
    std::list<NoeudServeur> zoneParcourable;

    //On regarde si le vaisseau peut se déplacer
    if (cellule[positionVaisseau.x][positionVaisseau.y].distanceMaximale(energie) > 0) {

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
                                  .distanceMaximale(energie);

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
                            NoeudServeur(*pointCourant,
                                         cellule[pointCourant->x][pointCourant->y].getCoutDeplacement(),
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

bool PlateauServeur::deplacerVaisseau(Position p1, Position p2, std::list<NoeudServeur> zoneParcourable, JoueurServeur& joueur) {
    std::list<NoeudServeur>::iterator noeudIterateur = zoneParcourable.begin();
    std::list<Position> chemin;
    sf::Int32 tailleChemin;

    if(cellule[p1.x][p1.y].possedeVaisseau() != cellule[p2.x][p2.y].possedeVaisseau()) {
        while (noeudIterateur != zoneParcourable.end()) {
            if (p2 == (noeudIterateur->getPosition())) {
                cellule[p1.x][p1.y].echangerVaisseau(cellule[p2.x][p2.y]);

                VaisseauServeurPtr v = cellule[p2.x][p2.y].getVaisseauPtr();

                chemin = obtenirChemin(p2, zoneParcourable);
                tailleChemin = chemin.size();

                joueur.setEnergie(joueur.getEnergie() - (v->getConsommation() * tailleChemin));
                joueur.setCommandement(joueur.getCommandement() - 1);
                return true;
            } else {
                noeudIterateur++;
            }
        }
    }

    return false;
}

int PlateauServeur::attaquer(Position attaquant, Position cible, JoueurServeur& joueur) {
    CelluleServeur *cAttaquant, *cCible;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;

    cAttaquant = &cellule[attaquant.x][attaquant.y];
    cCible = &cellule[cible.x][cible.y];

    noeuds = getZoneAttaquable(attaquant);

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        if(noeudIterator->getPosition() == cible) {
            joueur.setCommandement(joueur.getCommandement() - 1);
            return cAttaquant->attaquer(cCible);
        }
    }

    return -1;
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

//toast
void PlateauServeur::effectuerTour() {
    //Boucle de création d'un évènement par tour, au plus.
    sf::Int32 var = (sf::Int32)(rand() % 5);
    sf::Int32 xSpawn = (sf::Int32)(rand() % 10 + 4);
    sf::Int32 ySpawn = (sf::Int32)(rand() % 10 + 4);
    xSpawn = (sf::Int32)1;
    ySpawn = (sf::Int32)1;
    if (!cellule[xSpawn][ySpawn].getEvenement() 
     && !cellule[xSpawn][ySpawn].getBatiment()
     && !cellule[xSpawn][ySpawn].getVaisseau()) {
        switch (var) {
            case 0:
                cellule[xSpawn][ySpawn].creerEvenementTest(TypeEvenement::NuageGaz);
            break;
            case 1:
                cellule[xSpawn][ySpawn].creerEvenementTest(TypeEvenement::ChampMeteor);
            break;
            case 2:
                cellule[xSpawn][ySpawn].creerEvenementTest(TypeEvenement::Epave);
            break;
            case 3:
                cellule[xSpawn][ySpawn].creerEvenementTest(TypeEvenement::InfluenceTrouNoir);
            break;
            case 4:
                cellule[xSpawn][ySpawn].creerEvenementTest(TypeEvenement::StationSpatialeAbandonnee);
            break;
        } 
    }

    // Boucle d'action des évènements en fin de tour.
    for (sf::Int32 x = 0; x < tailleX; ++x) {
        for (sf::Int32 y = 0; y < tailleY; ++y) {    
            if(cellule[x][y].getEvenement()) {
                switch (cellule[x][y].getEvenement()->quelType()) {
                    
                    case TypeEvenement::InfluenceTrouNoir:
                        if (cellule[x][y].getVaisseauPtr())
                            cellule[x][y].getVaisseauPtr().reset();
                        if (cellule[x][y].getBatiment())
                            cellule[x][y].getBatiment().reset();
                        
                        for (int i = -1; i < 2; i++) {
                            for(int j = -1; j < 2; j++) {
                                if (cellule[x+i][y+j].getVaisseauPtr())
                                    cellule[x+i][y+j].getVaisseauPtr()->setVie(cellule[x+i][y+j].getVaisseauPtr()->getVie() / 2);
                                if (cellule[x+i][y+j].getBatiment())
                                    cellule[x+i][y+j].getBatiment()->setVie(cellule[x+i][y+j].getBatiment()->getVie() / 2);
                            }
                        }
                    break;
                    
                    case TypeEvenement::ChampMeteor:
                        for (int i = -1; i < 2; i++) {
                            for(int j = -1; j < 2; j++) {
                                if (cellule[x+i][y+j].getVaisseauPtr())
                                    cellule[x+i][y+j].getVaisseauPtr()->setVie(cellule[x+i][y+j].getVaisseauPtr()->getVie() - 20);
                                if (cellule[x+i][y+j].getBatiment())
                                    cellule[x+i][y+j].getBatiment()->setVie(cellule[x+i][y+j].getBatiment()->getVie() - 20);
                            }
                        }
                    break;

                    case TypeEvenement::NuageGaz:
                        if (cellule[x][y].getVaisseauPtr())
                            cellule[x][y].getVaisseauPtr()->setBouclier(0);
                    break;

                    default :
                    break;
                } 
            }
        }
    }
}

std::vector<BatimentServeur>* PlateauServeur::getListeConstruction(Position position, sf::Int32 idJoueur) {
    if(cellule[position.x][position.y].possedeVaisseau()
            && cellule[position.x][position.y].getVaisseau()->getType() == TypeVaisseau::Constructeur
            && cellule[position.x][position.y].getVaisseau()->getIdJoueur() == idJoueur) {
                VaisseauServeur* vaisseau = cellule[position.x][position.y].getVaisseauPtr().get();
                Constructeur* constructeur = dynamic_cast<Constructeur*>(vaisseau);
                return constructeur->getListeConstruction();
            }
                
    return nullptr;
}
