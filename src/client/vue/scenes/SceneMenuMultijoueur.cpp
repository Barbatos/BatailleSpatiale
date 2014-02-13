/*
 * SceneMenuMultijoueur.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */

#include "SceneMenuMultijoueur.hpp"

#include <client/Jeu.hpp>
#include <client/vue/gui/elements/generiques/ZoneTexte.hpp>

SceneMenuMultijoueur::SceneMenuMultijoueur(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 2;
    int hauteur = 86 / 2;

    int x = (affichage.getSize().x - largeur) / 2;

    int y = (affichage.getSize().y - hauteur) / 6;

    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    pseudo = new ZoneTexte(&gui, -1, x, y, largeur, hauteur, "Pseudo");

    ip = new ZoneTexte(&gui, -1, x, 2 * y, largeur, hauteur, "IP");

    port = new ZoneTexte(&gui, -1, x, 3 * y, largeur, hauteur, "Port");

    new Bouton(&gui, Multijoueur, "Lancer partie", x, 4 * y, largeur, hauteur);
    new Bouton(&gui, Retour, "Retour", x, 5 * y, largeur, hauteur);
}

SceneMenuMultijoueur::~SceneMenuMultijoueur() {
    delete ip;
    delete port;
    delete pseudo;
}

void SceneMenuMultijoueur::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Multijoueur:
                    jeu.lireReseau()->ConnexionServeur(ip->lireTexte(), std::atoi(port->lireTexte().c_str()), false);
                    jeu.lireReseau()->EnvoyerPseudoServeur(pseudo->lireTexte());
                    jeu.changer(Scene::SceneChargementJeuMulti);
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
