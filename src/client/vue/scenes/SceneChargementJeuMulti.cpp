/*
 * SceneChargementJeuMulti.cpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Soinou
 */

#include "SceneChargementJeuMulti.hpp"

#include <client/vue/gui/elements/chargement/ChargementServeurs.hpp>
#include <client/vue/gui/elements/generiques/Bouton.hpp>

SceneChargementJeuMulti::SceneChargementJeuMulti(Jeu& jeu) :
        Scene(jeu) {
    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    int largeur = affichage.getSize().x / 2;
    int hauteur = affichage.getSize().y / 2;

    int x = (affichage.getSize().x - largeur) / 2;
    int y = (affichage.getSize().y - hauteur) / 2;

    new ChargementServeurs(&gui, 0, x, y, largeur, hauteur);

    largeur = 300 / 1.5;
    hauteur = 86 / 1.5;

    x = (affichage.getSize().x - largeur) / 2;
    y = affichage.getSize().y - hauteur - 50;

    new Bouton(&gui, 1, "Retour", x, y, largeur, hauteur);

    jeu.lireReseau()->demanderListeServeurs();
}

SceneChargementJeuMulti::~SceneChargementJeuMulti() {

}

void SceneChargementJeuMulti::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case 0:
                    lireJeu().changer(Scene::SceneListeServeurs);
                    break;
                case 1:
                    lireJeu().changer(Scene::SceneMenuPrincipal);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
