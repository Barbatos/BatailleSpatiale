/*
 * AffichageConstructions.cpp
 *
 *  Created on: 26 janv. 2014
 *      Author: Gabriel
 */

#include "AffichageConstructions.hpp"

#include "BoutonConstruction.hpp"

AffichageConstructions::AffichageConstructions(Gui* gui, int id, int x, int y,
        int largeur, int hauteur) :
        Element(gui, id), vaisseaux(), batiments() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    int tailleX = largeur / 8;
    int tailleY = hauteur / 2;

    ajouterBouton(TypeVaisseau::Constructeur, x, y, tailleX, tailleY);
    ajouterBouton(TypeVaisseau::Leger, x + tailleX + 5, y, tailleX, tailleY);
    ajouterBouton(TypeVaisseau::Traqueur, x + 2 * (tailleX + 5), y, tailleX,
            tailleY);
    ajouterBouton(TypeVaisseau::Chasseur, x + 3 * (tailleX + 5), y, tailleX,
            tailleY);
    ajouterBouton(TypeVaisseau::ChasseurLourd, x + 4 * (tailleX + 5), y,
            tailleX, tailleY);
    ajouterBouton(TypeVaisseau::Bombardier, x + 5 * (tailleX + 5), y, tailleX,
            tailleY);
    ajouterBouton(TypeVaisseau::Croiseur, x + 6 * (tailleX + 5), y, tailleX,
            tailleY);
    ajouterBouton(TypeVaisseau::Destructeur, x + 7 * (tailleX + 5), y, tailleX,
            tailleY);

    tailleX = largeur / 3;

    ajouterBouton(TypeBatiment::ChantierSpatial, x, y + tailleY, tailleX,
            tailleY);
    ajouterBouton(TypeBatiment::Mine, x + tailleX, y + tailleY, tailleX,
            tailleY);
    ajouterBouton(TypeBatiment::Raffinerie, x + 2 * tailleX, y + tailleY,
            tailleX, tailleY);
}

AffichageConstructions::~AffichageConstructions() {
    for (std::list<BoutonConstruction*>::iterator vaisseau = vaisseaux.begin();
            vaisseau != vaisseaux.end(); vaisseau++) {
        vaisseau = vaisseaux.erase(vaisseau);

        if (*vaisseau != nullptr)
            delete (*vaisseau);
    }

    for (std::list<BoutonConstruction*>::iterator batiment = batiments.begin();
            batiment != batiments.end(); batiment++) {
        batiment = batiments.erase(batiment);

        if (*batiment != nullptr)
            delete (*batiment);
    }
}

void AffichageConstructions::actualiser(float) {

}

void AffichageConstructions::afficher() {

}

bool AffichageConstructions::contient(sf::Vector2i) {
    return false;
}

void AffichageConstructions::ajouterBouton(TypeVaisseau type, int x, int y,
        int largeur, int hauteur) {
    BoutonConstruction* bouton = new BoutonConstruction(lireGui(), -1, x, y,
            largeur, hauteur);

    bouton->ecrireType(type);

    vaisseaux.push_back(bouton);
}

void AffichageConstructions::ajouterBouton(TypeBatiment type, int x, int y,
        int largeur, int hauteur) {
    BoutonConstruction* bouton = new BoutonConstruction(lireGui(), -1, x, y,
            largeur, hauteur);

    bouton->ecrireType(type);

    batiments.push_back(bouton);
}

void AffichageConstructions::ecrireVaisseauxVisibles(bool visible) {
    for (BoutonConstruction* bouton : vaisseaux)
        bouton->ecrireVisible(visible);
}

void AffichageConstructions::ecrireBatimentsVisibles(bool visible) {
    for (BoutonConstruction* bouton : batiments)
        bouton->ecrireVisible(visible);
}
