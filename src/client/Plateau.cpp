#include "Plateau.hpp"

Plateau::Plateau(__attribute__((unused)) std::string adresseServeur) {
    /* Connexion reseau */
    //Si la connexion échoue renvoyer une exception
    
    numeroJoueur = 1;
    tailleX = 10;
    tailleY = 12;
    
    // Allocation de la mémoire
    cellule.resize(tailleX, std::vector<Cellule>(tailleY));
    
    //Affectation du plateau
    for (int x = 0 ; x < tailleX ; ++x)
        for (int y = 0 ; y < tailleY ; ++y)
            cellule[x][y] = Cellule();
    
    cellule[0][0].setVaisseau(new Vaisseau((DetailVaisseau){TypeVaisseau::Simple, 45, 50, 10, 10, 0.1f, 5, 6, 8}));
    
    /* Fin connexion */
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

bool Plateau::deplacerVaisseau(Position depart, Position arrivee) {
    if(depart.x < tailleX && arrivee.x < tailleX &&
    depart.x >= 0 && arrivee.x >= 0 &&
    depart.y < tailleY && arrivee.y < tailleY &&
    depart.y >= 0 && arrivee.y >= 0){
        cellule[arrivee.x][arrivee.y].echangerVaisseau(cellule[depart.x][depart.y]);
        return true;
    }
    return false;
}
