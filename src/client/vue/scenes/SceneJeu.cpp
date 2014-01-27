/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/vues/BoutonDeplacementPlateau.hpp>

#include <client/vue/gui/elements/vues/AffichageDetails.hpp>
#include <client/vue/gui/elements/vues/AffichageCase.hpp>

#include <client/Jeu.hpp>

#include <client/modele/Plateau.hpp>

SceneJeu::SceneJeu(Jeu& jeu)
                : Scene(jeu), vue(sf::FloatRect(0, 0, 0, 0)) {
    // On change le viewport de la vue
    vue.setViewport(sf::FloatRect(0.01f, 0.01f, 0.98f, 0.68f));

    gui.ajouterObservateurSouris(this);

    int winx = jeu.lireAffichage().getSize().x;
    int winy = jeu.lireAffichage().getSize().y;

    float x = winx * 0.01f;
    float y = winy * 0.01f;

    new Image(&gui, 100, 0, 0, winx, winy, jeu.lireRessources().lireImage("fond.png"));

    details = new AffichageDetails(&gui, Details, x, 0.7 * winy, winx - 2 * x, 0.3 * winy - y);

    initialiserPlateau();

    new BoutonDeplacementPlateau(&gui, Droite, winx - x, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Gauche, 0, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Haut, 0, 0, winx, y);
    new BoutonDeplacementPlateau(&gui, Bas, 0, winy - y, winx, y);

    new Bouton(&gui, Menu, "Menu", (winx - 100) / 2, winy - 40 - y, 100, 40);

    action = new Bouton(&gui, Action, "Action", (winx - 100) / 2, 0.7 * winy, 100, 40);

    action->ecrireVisible(false);
}

SceneJeu::~SceneJeu() {
    for (AffichageCase* c : cases)
        delete c;

    cases.clear();

    delete action;
}

void SceneJeu::initialiserPlateau() {
    jeu.lirePlateau().viderZones();

    // On récupère la taille de la fenêtre
    int winx = lireJeu().lireAffichage().getSize().x;
    int winy = lireJeu().lireAffichage().getSize().y;

    // On calcule la taille des boutons sur les côtés
    float x = winx * 0.01f;
    float y = winy * 0.01f;

    // On récupère le plateau
    Plateau & p = jeu.lirePlateau();

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
                AffichageCase* c = new AffichageCase(&lireGui(), -1, xc, yc, taille, Position(i, j), &vue);

                // On ajoute la case à la liste de cases
                cases.push_back(c);
            }
        }

    // On change la taille de la vue
    if (xc > yc)
        taille = yc;
    else
        taille = xc;

    vue.setSize((winx - 2 * x) / 2, (winy - 2 * y) / 2);
    vue.move(taille / 2, taille / 2);
}

void SceneJeu::appuiCase(Message::MessageCellule message) {

    Plateau & p = lireJeu().lirePlateau();

    if (message.x == -1 && message.y == -1) {
        p.viderChemin();
        p.viderZoneParcourable();
        details->selectionner();
        return;
    }

    ReseauClient* r = lireJeu().lireReseau().get();
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
}

void SceneJeu::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Menu:
                    jeu.changer(Scene::SceneJeuMenu);
                    break;
                case Droite:
                    if (vue.getCenter().x
                                    <= ((jeu.lirePlateau().getTailleX()
                                                    + jeu.lirePlateau().getTailleY() / 2) * 30))
                        vue.move(5, 0);
                    break;
                case Gauche:
                    if (vue.getCenter().x >= 0)
                        vue.move(-5, 0);
                    break;
                case Haut:
                    if (vue.getCenter().y >= 0)
                        vue.move(0, -5);
                    break;
                case Bas:
                    if (vue.getCenter().y
                                    <= ((jeu.lirePlateau().getTailleY()
                                                    + jeu.lirePlateau().getTailleX() / 2) * 30))
                        vue.move(0, 5);
                    break;
                default:
                    break;
            }
            break;
        case Message::Cellule:
            appuiCase(message.cellule);
            break;
        default:
            break;
    }
}

// Héritées d'ElementSouris
void SceneJeu::clicSouris(bool) {
}

void SceneJeu::pressionSouris(sf::Mouse::Button) {

}

void SceneJeu::relachementSouris(sf::Mouse::Button bouton) {
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
void SceneJeu::entreeSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void SceneJeu::sortieSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void SceneJeu::moletteSouris(int delta) {
    if (delta <= 0 && vue.getSize().x < 2000)
        vue.zoom(1.1);
    else if (delta >= 0 && vue.getSize().x > 100)
        vue.zoom(0.9);
}
