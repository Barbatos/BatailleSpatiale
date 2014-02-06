/*
 * SceneOptionsMenu.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */
#include "SceneOptionsMenu.hpp"

#include <client/Jeu.hpp>

SceneOptionsMenu::SceneOptionsMenu(Jeu& jeu)
                : Scene(jeu) {
    int largeur = 300 / 2;
    int hauteur = 86 / 2;

    int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

    int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

    new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x, jeu.lireAffichage().getSize().y, jeu.lireRessources().lireImage("fond.png"));

    new Bouton(&gui, Musique, "Musique", x, y / 2, largeur, hauteur);
    new Bouton(&gui, AugmenterMusique, "+", 1.25 * x, 1.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, BaisserMusique, "-", 0.75 * x, 1.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, Son, "Son", x, 2 * y / 2, largeur, hauteur);
    new Bouton(&gui, AugmenterSon, "+", 1.25 * x, 2.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, BaisserSon, "-", 0.75 * x, 2.3 * y / 2, largeur, hauteur);
    new Bouton(&gui, Retour, "Retour", x, 2 * y, largeur, hauteur);

    //musique = jeu.lireRessources().lireMusique("game_soundtrack_low.ogg");
}

SceneOptionsMenu::~SceneOptionsMenu() {
}

void SceneOptionsMenu::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Retour:
                    jeu.changer(Scene::SceneMenuPrincipal);
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
