/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeuOptions.hpp"

#include <client/Jeu.hpp>

SceneJeuOptions::SceneJeuOptions(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 2;
    int hauteur = 86 / 2;

    int x = (affichage.getSize().x - largeur) / 2;

    int y = (affichage.getSize().y - hauteur) / 2;

    new Image(&gui, 100, 0, 0, affichage.getSize().x, affichage.getSize().y, jeu.lireRessources().lireImage("fond.png"));

    new Bouton(&gui, Musique, "Musique", x, y / 2, largeur, hauteur);
    new Bouton(&gui, AugmenterMusique, "+", 1.25 * x, 1.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, BaisserMusique, "-", 0.75 * x, 1.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, Son, "Son", x, 2 * y / 2, largeur, hauteur);
    new Bouton(&gui, AugmenterSon, "+", 1.25 * x, 2.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, BaisserSon, "-", 0.75 * x, 2.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, Retour, "Retour", x, 2 * y, largeur, hauteur);
}

SceneJeuOptions::~SceneJeuOptions() {
}

void SceneJeuOptions::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Retour:
                    jeu.changer(Scene::SceneJeu);
                    break;
                case Musique:
                	lireJeu().lireGestionnaire()->playPauseChanson();
                    break;
                case Son:
                    if (lireJeu().lireRessources().estSilencieuxSons() == false)
                        lireJeu().lireRessources().silenceSons();
                    else
                        lireJeu().lireRessources().nonSilenceSons();
                    break;
                case AugmenterMusique:
                    if (lireJeu().lireRessources().obtenirVolumeMusiques() < 100) {
                        lireJeu().lireRessources().changerVolumeMusiques(lireJeu().lireRessources().obtenirVolumeMusiques() + 1);
                    }
                    break;
                case BaisserMusique:
                    if (lireJeu().lireRessources().obtenirVolumeMusiques() > 0) {
                        lireJeu().lireRessources().changerVolumeMusiques(lireJeu().lireRessources().obtenirVolumeMusiques() - 1);
                    }
                    break;
                case AugmenterSon:
                    if (lireJeu().lireRessources().obtenirVolumeSons() < 100) {
                        lireJeu().lireRessources().changerVolumeSons(lireJeu().lireRessources().obtenirVolumeSons() + 1);
                    }
                    break;
                case BaisserSon:
                    if (lireJeu().lireRessources().obtenirVolumeSons() > 0) {
                        lireJeu().lireRessources().changerVolumeSons(lireJeu().lireRessources().obtenirVolumeSons() - 1);
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
