/*
 * AffichagePlateau.cpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#include "AffichagePlateau.hpp"

#include <client/Jeu.hpp>

AffichagePlateau::AffichagePlateau(Gui* gui, int id, int x, int y, int largeur, int hauteur, AffichageDetails::Ptr details)
                : Element(gui, id), ObservateurSouris(), details(details), cases(), vuePlateau(sf::FloatRect(0, 0, 0, 0)), charge(false)

{
    // Pour initialiser l'élément
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);
    ecrireVue(&vuePlateau);

    // Pour dire que le plateau intéragit avec la souris
    enregistrerSouris(ObservateurSouris::Ptr(this));

    // On change le viewport de la vue
    vuePlateau.setViewport(sf::FloatRect(0, 0, 1, 0.7f));

    // On récupère les tailles du plateau
    int maxx = lireGui()->lireScene()->lireJeu().lirePlateau().getTailleX();
    int maxy = lireGui()->lireScene()->lireJeu().lirePlateau().getTailleY();

    // On initialise la taille des cellules
    int taille = 25;

    // On initialise les positions en x et y des cellules
    int xc = 0;
    int yc = 0;

    // On parcoure les cases du plateau
    for (int i = 0; i < maxx; i++)
        for (int j = 0; j < maxy; j++) {
            // On calcule la position en x et y
            xc = (i * 2 + j) * taille * 3 / 5;
            yc = j * taille;

            // On initialise l'affichage de la case
            AffichageCase* c = new AffichageCase(lireGui(), SceneJeu::Case, xc, yc, taille, Position(i, j), &vuePlateau);

            // On ajoute la case à la liste de cases
            cases.push_back(AffichageCase::Ptr(c));
        }

    // On change la taille de la vue
    if (xc > yc)
        taille = yc;
    else
        taille = xc;

    vuePlateau.setSize(largeur, hauteur);
    vuePlateau.move(taille / 2, taille / 2);
}

AffichagePlateau::~AffichagePlateau() {
    for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size(); i++)
        cases[i].reset();

    cases.clear();
}

void AffichagePlateau::actualiser(float) {

}

void AffichagePlateau::bougerPlateau(float x, float y) {
    vuePlateau.move(x, y);
}

void AffichagePlateau::appuiCase() {
    bool selection = false;
    Position position;

    // On vide la zone parcourable du plateau
    lireGui()->lireScene()->lireJeu().lirePlateau().viderZoneParcourable();

    // Pour toutes les cases, et tant que rien n'a été selectionné
    for (std::vector<AffichageCase::Ptr>::size_type i = 0; !selection && i < cases.size(); i++) {
        // Si la case est selectionnée
        if (cases[i]->lireSelectionne()) {
            // On stocke la position de la case selectionnée
            Position posCase = cases[i]->lirePositionPlateau();

            // On sauvegarde la position actuellement selectionnée
            position = details->lirePosition();
            // On selectionne la nouvelle
            details->selectionner(selection);
            // On dit que quelque chose a été selectionné
            selection = true;

            // On stocke la case et on vérifie si c'est un vaisseau
            TypeCellule c = lireGui()->lireScene()->lireJeu().lirePlateau().getCellule(posCase).statutEmplacement();
            if (c == TypeCellule::Vaisseau)
                // Si oui, on demande au serveur la zone parcourable
                lireGui()->lireScene()->lireJeu().lireReseau()->getZoneParcourable(posCase);
        }
    }

    // Si rien n'a été selectionné
    if (!selection) {
        // Ne rien selectionner
        details->selectionner();
    }
    // Sinon
    else {
        // Si une case était précédemment selectionnée
        if (position.x != -1 && position.y != -1) {
            // On récupère la nouvelle position
            // Position nouvelle = details->lirePosition();

            // Si la précédente case selectionnée contenait un vaisseau
            if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeVaisseau(position)) {
                // On déplace ce vaisseau
            }
            // Sinon, si c'était un bâtiment
            else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeBatiment(position)) {
                // Faire quelque chose
            }
        }
    }
}

void AffichagePlateau::afficher(sf::RenderWindow&) {

}

bool AffichagePlateau::contient(sf::Vector2i) {
    return false;
}

// Héritées d'ElementSouris
void AffichagePlateau::clicSouris() {
    /* Ne rien faire ici */
}

void AffichagePlateau::pressionSouris(sf::Mouse::Button) {
}

void AffichagePlateau::relachementSouris(sf::Mouse::Button) {

}
void AffichagePlateau::entreeSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void AffichagePlateau::sortieSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void AffichagePlateau::moletteSouris(int delta) {
    if (delta <= 0 && vuePlateau.getSize().x < 2000)
        vuePlateau.zoom(1.1);
    else if (delta >= 0 && vuePlateau.getSize().x > 100)
        vuePlateau.zoom(0.9);
}

// Héritées d'ElementClavier
void AffichagePlateau::pressionTouche(sf::Keyboard::Key) {
    /* Ne rien faire ici */
}
void AffichagePlateau::relachementTouche(sf::Keyboard::Key) {

}
void AffichagePlateau::entreeTexte(sf::Uint32) {
    /* Ne rien faire ici */
}
