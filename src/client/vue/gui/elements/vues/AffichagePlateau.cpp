/*
 * AffichagePlateau.cpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#include "AffichagePlateau.hpp"

#include <client/Jeu.hpp>

#include "AffichageDetails.hpp"
#include "AffichageCase.hpp"

#include "Etat.hpp"

AffichagePlateau::AffichagePlateau(Gui* gui, int id, int x, int y, int largeur, int hauteur,
    AffichageDetails* details)
                : Element(gui, id), ObservateurSouris(), details(details), cases(),
                  vuePlateau(sf::FloatRect(0, 0, 0, 0))

{
    // Pour initialiser l'élément
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);
    ecrireVue(&vuePlateau);

    // On change le viewport de la vue
    vuePlateau.setViewport(sf::FloatRect(0.01f, 0.01f, 0.98f, 0.68f));

    // On récupère le plateau
    Plateau& p = lireGui()->lireScene()->lireJeu().lirePlateau();

    // Pour dire que le plateau intéragit avec la souris
    // En dernier, pour notifier l'état que les évènements des cases sont terminés et qu'on peut les gérer
    enregistrerSouris(this);

    // On récupère les tailles du plateau
    int maxx = p.getTailleX();
    int maxy = p.getTailleY();

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

            if (p.getCellule(Position(i, j)).statutEmplacement() != TypeCellule::Inexistant) {
                AffichageCase* c = new AffichageCase(lireGui(), -1, xc, yc, taille, Position(i, j), &vuePlateau);

                // On ajoute la case à la liste de cases
                cases.push_back(c);
            }
        }

    // On change la taille de la vue
    if (xc > yc)
        taille = yc;
    else
        taille = xc;

    vuePlateau.setSize(largeur, hauteur);
    vuePlateau.move(taille / 2, taille / 2);

    etat = new Etat(details, &(lireGui()->lireScene()->lireJeu()));
}

AffichagePlateau::~AffichagePlateau() {
    for (std::vector<AffichageCase*>::size_type i = 0; i < cases.size(); i++)
        delete cases[i];

    cases.clear();

    delete etat;
}

void AffichagePlateau::actualiser(float) {

}

void AffichagePlateau::bougerPlateau(float x, float y) {
    vuePlateau.move(x, y);
}

void AffichagePlateau::appuiCase(Message::MessageCellule message) {

    Plateau& p = lireGui()->lireScene()->lireJeu().lirePlateau();

    if (message.x == -1 && message.y == -1) {
        p.viderChemin();
        p.viderZoneParcourable();
        details->selectionner();
        return;
    }

    ReseauClient* r = lireGui()->lireScene()->lireJeu().lireReseau().get();
    Position ancienne = details->lirePosition();
    Position position = Position(message.x, message.y);

    // Si une case était précédemment selectionnée
    if (ancienne.x != -1 && ancienne.y != -1) {
        if (p.getCellule(ancienne).statutEmplacement() == TypeCellule::Vaisseau) {
            if (message.clicDroit) {
                p.viderChemin();
                r->getChemin(ancienne, position);
            }
            else {
                // Déplacement, Attaque, etc
                r->demanderDeplacementVaisseau(ancienne, position);
            }
        }
    }

    if (!message.clicDroit) {
        p.viderChemin();
        p.viderZoneParcourable();

        details->selectionner(position);

        if (p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau) {
            if (p.getVaisseau(position).type == TypeVaisseau::Constructeur)
                r->getZoneConstructibleVaisseau(position);

            r->getZoneParcourable(position);
        }
        else if (p.getCellule(position).statutEmplacement() == TypeCellule::Batiment
                        && p.getBatiment(position).type == TypeBatiment::Base)
            r->getZoneConstructibleBatiment(position);
    }

    // etat->appuiCase(message);
}

void AffichagePlateau::afficher(sf::RenderWindow&) {

}

bool AffichagePlateau::contient(sf::Vector2i) {
    return false;
}

// Héritées d'ElementSouris
void AffichagePlateau::clicSouris(bool) {
}

void AffichagePlateau::pressionSouris(sf::Mouse::Button) {

}

void AffichagePlateau::relachementSouris(sf::Mouse::Button bouton) {
    //etat->appuiPlateau();
    if (bouton == sf::Mouse::Right)
        return;

    Message::MessageCellule message;

    message.x = -1;
    message.y = -1;

    message.clicDroit = false;
    message.selection = false;
    appuiCase(message);

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
