/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/vues/BoutonDeplacementPlateau.hpp>

#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu)
                : Scene(jeu) {
    jeu.lirePlateau().viderZoneParcourable();

    int winx = jeu.lireAffichage().getSize().x;
    int winy = jeu.lireAffichage().getSize().y;

    new Image(&gui, 100, 0, 0, winx, winy, jeu.lireRessources().lireImage("fond.png"));

    float x = winx * 0.01f;
    float y = winy * 0.01f;

    details = AffichageDetails::Ptr(new AffichageDetails(&gui, Details, x, 0.7 * winy, winx / 3 - x, 0.3
                    * winy - y));

    plateau = AffichagePlateau::Ptr(new AffichagePlateau(&gui, Plateau, 0, 0, (winx - 2 * x) / 2, (winy
                    - 2 * y) / 2, details));

    new BoutonDeplacementPlateau(&gui, Droite, winx - x, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Gauche, 0, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Haut, 0, 0, winx, y);
    new BoutonDeplacementPlateau(&gui, Bas, 0, winy - y, winx, y);

    new Bouton(&gui, Menu, "Menu", (winx - 100) / 2, winy - 40 - y, 100, 40);
}

SceneJeu::~SceneJeu() {

}

void SceneJeu::surMessage(Message message) {
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Menu:
                    jeu.changer(Scene::SceneJeuMenu);
                    break;
                case Plateau:
                    break;
                case Droite:
                    plateau->bougerPlateau(5, 0);
                    break;
                case Gauche:
                    plateau->bougerPlateau(-5, 0);
                    break;
                case Haut:
                    plateau->bougerPlateau(0, -5);
                    break;
                case Bas:
                    plateau->bougerPlateau(0, 5);
                    break;
                default:
                    break;
            }
            break;
        case Message::Cellule:
            plateau->appuiCase(message.cellule);
            break;
        default:
            break;
    }
}
