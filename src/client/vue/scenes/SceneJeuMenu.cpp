/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeuMenu.hpp"

#include <client/Jeu.hpp>

SceneJeuMenu::SceneJeuMenu(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 1.5;
    int hauteur = 86 / 1.5;

    int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

    int y = (jeu.lireAffichage().getSize().y - hauteur) / 7;

    new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x, jeu.lireAffichage().getSize().y, jeu.lireRessources().lireImage("fond.png"));

    new Bouton(&gui, Retour, "Retour au jeu", x, y, largeur, hauteur);
    new Bouton(&gui, Sauvegarder, "Sauvegarder la partie", x, 2 * y, largeur, hauteur);
    new Bouton(&gui, Charger, "Charger une partie", x, 3 * y, largeur, hauteur);
    new Bouton(&gui, Options, "Options", x, 4 * y, largeur, hauteur);
    new Bouton(&gui, QuitterPartie, "Quitter la partie", x, 5 * y, largeur, hauteur);
    new Bouton(&gui, QuitterJeu, "Quitter le jeu", x, 6 * y, largeur, hauteur);
}

SceneJeuMenu::~SceneJeuMenu() {
}

void SceneJeuMenu::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Retour:
                    jeu.changer(Scene::SceneJeu);
                    break;
                case QuitterJeu:
                    jeu.quitter();
                    break;
                case QuitterPartie:
                    jeu.changer(Scene::SceneMenuPrincipal);
                    break;
                case Options:
                    jeu.changer(Scene::SceneJeuOptions);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
