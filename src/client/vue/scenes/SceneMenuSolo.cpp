/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneMenuSolo.hpp"

#include <client/Jeu.hpp>

SceneMenuSolo::SceneMenuSolo(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 2;
    int hauteur = 86 / 2;

    int x = (affichage.getSize().x - largeur) / 2;

    int y = (affichage.getSize().y - hauteur) / 3;

    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    new Bouton(&gui, Solo, "Lancer partie", x, y, largeur, hauteur);

    new Bouton(&gui, Retour, "Retour", x, 2 * y, largeur, hauteur);
}

SceneMenuSolo::~SceneMenuSolo() {
}

void SceneMenuSolo::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Solo:
                    if (!jeu.lireReseau()->getActif()) {
                        jeu.lancerServeurGUI(1337, true);
                        jeu.lireReseau()->ConnexionServeur("127.0.0.1", 1337, true);
                    }
                    jeu.changer(Scene::SceneChargementJeu);
                    break;
                case Retour:
                    jeu.changer(Scene::SceneMenuPrincipal);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
