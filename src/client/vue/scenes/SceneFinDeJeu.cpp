/*
 * SceneFinDeJeu.cpp
 *
 *  Created on: 26 févr. 2014
 *      Author: Soinou
 */

#include "SceneFinDeJeu.hpp"

#include <client/vue/Affichage.hpp>
#include <client/vue/gui/elements/generiques/TexteFinDeJeu.hpp>

SceneFinDeJeu::SceneFinDeJeu(Jeu& jeu) :
        Scene(jeu) {
    int largeur = 300 / 1.5;
    int hauteur = 86 / 1.5;

    new Image(&gui, -1, 0, 0, affichage.getSize().x, affichage.getSize().y,
    jeu.lireRessources().lireImage("fond.png"));

    new TexteFinDeJeu(&gui, -1, affichage.getSize().x / 2, affichage.getSize().y / 2);

    new Bouton(&gui, 1, "Retour au menu principal", (affichage.getSize().x - largeur) / 2, affichage.getSize().y - hauteur - 50, largeur, hauteur);
}

SceneFinDeJeu::~SceneFinDeJeu() {
}

void SceneFinDeJeu::surMessage(Message message) {
    if (message.type == Message::Element && message.element.id == 1)
        jeu.changer(Scene::SceneMenuPrincipal);
}
