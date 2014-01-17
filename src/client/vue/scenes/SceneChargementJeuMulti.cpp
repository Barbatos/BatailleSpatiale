/*
 * SceneChargementJeuMulti.cpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Soinou
 */

#include "SceneChargementJeuMulti.hpp"

#include <client/vue/gui/elements/chargement/ChargementReseau.hpp>
#include <client/vue/gui/elements/generiques/Bouton.hpp>

SceneChargementJeuMulti::SceneChargementJeuMulti(Jeu& jeu)
                : Scene(jeu) {
    new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x, jeu.lireAffichage().getSize().y, jeu.lireRessources().lireImage("fond.png"));

    int largeur = jeu.lireAffichage().getSize().x / 2;
    int hauteur = jeu.lireAffichage().getSize().y / 2;

    int x = (jeu.lireAffichage().getSize().x - largeur) / 2;
    int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

    new ChargementReseau(&gui, 0, x, y, largeur, hauteur);

    largeur = 300 / 1.5;
    hauteur = 86 / 1.5;

    x = (jeu.lireAffichage().getSize().x - largeur) / 2;
    y = jeu.lireAffichage().getSize().y - hauteur - 50;

    new Bouton(&gui, 1, "Retour", x, y, largeur, hauteur);
}

SceneChargementJeuMulti::~SceneChargementJeuMulti() {

}

void SceneChargementJeuMulti::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case 0:
                    lireJeu().changer(Scene::SceneJeu);
                    break;
                case 1:
                    lireJeu().changer(Scene::SceneMenuMulti);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
