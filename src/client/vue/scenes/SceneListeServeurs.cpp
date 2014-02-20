/*
 * SceneListeServeurs.cpp
 *
 *  Created on: 18 févr. 2014
 *      Author: Soinou
 */

#include "SceneListeServeurs.hpp"

#include <client/vue/gui/elements/generiques/ListeServeurs.hpp>
#include <client/vue/gui/elements/generiques/Bouton.hpp>

SceneListeServeurs::SceneListeServeurs(Jeu& jeu) :
        Scene(jeu) {

    int largeur = 300 / 1.5;
    int hauteur = 86 / 1.5;

    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    new ListeServeurs(&gui, 0, 0, 0, affichage.getSize().x, affichage.getSize().y - hauteur);

    new Bouton(&gui, 1, "Retour", (affichage.getSize().x - largeur)/ 2, affichage.getSize().y - hauteur - 10, largeur, hauteur);

    jeu.lireReseau()->demanderListeServeurs();
}

SceneListeServeurs::~SceneListeServeurs() {
}

void SceneListeServeurs::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case 0:
                    lireJeu().changer(Scene::SceneMenuMulti);
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
