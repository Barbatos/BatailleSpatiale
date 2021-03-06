/*
 * SceneLancerServeur.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Barbatos
 */

#include "SceneLancerServeur.hpp"

#include <client/Jeu.hpp>

#include <commun/ReseauServeur.hpp>

SceneLancerServeur::SceneLancerServeur(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 2;
    int hauteur = 86 / 2;

    int x = (affichage.getSize().x - largeur) / 2;

    int y = (affichage.getSize().y - hauteur) / 5;

    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    port = new ZoneTexte(&gui, Port, x, 2 * y, largeur, hauteur, "Port du serveur");

    new Bouton(&gui, Serveur, "Lancer le serveur", x, 3 * y, largeur, hauteur);

    new Bouton(&gui, Retour, "Retour", x, 4 * y, largeur, hauteur);
}

SceneLancerServeur::~SceneLancerServeur() {
}

void SceneLancerServeur::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Retour:
                    jeu.changer(Scene::SceneMenuPrincipal);
                    break;
                case Serveur:
                    jeu.lancerServeurGUI(atoi(port->lireTexte().c_str()), false);
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
