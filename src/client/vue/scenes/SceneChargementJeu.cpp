/*
 * SceneChargementJeu.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "SceneChargementJeu.hpp"

#include <client/vue/gui/elements/chargement/ChargementReseau.hpp>
#include <client/vue/gui/elements/generiques/Bouton.hpp>

SceneChargementJeu::SceneChargementJeu(Jeu& jeu)
                : Scene(jeu) {
    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    int largeur = affichage.getSize().x / 2;
    int hauteur = affichage.getSize().y / 2;

    int x = (affichage.getSize().x - largeur) / 2;
    int y = (affichage.getSize().y - hauteur) / 2;

    new ChargementReseau(&gui, 0, x, y, largeur, hauteur);

    largeur = 300 / 1.5;
    hauteur = 86 / 1.5;

    x = (affichage.getSize().x - largeur) / 2;
    y = affichage.getSize().y - hauteur - 50;

    new Bouton(&gui, 1, "Retour", x, y, largeur, hauteur);
}

SceneChargementJeu::~SceneChargementJeu() {
}

void SceneChargementJeu::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case 0:
                    lireJeu().changer(Scene::SceneJeu);
                    break;
                case 1:
                    lireJeu().changer(Scene::SceneMenuSolo);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
