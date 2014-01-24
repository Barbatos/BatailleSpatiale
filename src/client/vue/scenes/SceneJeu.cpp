/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/vues/BoutonDeplacementPlateau.hpp>

#include <client/vue/gui/elements/vues/AffichageDetails.hpp>
#include <client/vue/gui/elements/vues/AffichagePlateau.hpp>

#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu)
: Scene(jeu) {
    jeu.lirePlateau().viderZones();

    int winx = jeu.lireAffichage().getSize().x;
    int winy = jeu.lireAffichage().getSize().y;

    new Image(&gui, 100, 0, 0, winx, winy, jeu.lireRessources().lireImage("fond.png"));

    float x = winx * 0.01f;
    float y = winy * 0.01f;

    details = new AffichageDetails(&gui, Details, x, 0.7 * winy, winx - 2 * x, 0.3
                                   * winy - y);

    plateau = new AffichagePlateau(&gui, Plateau, 0, 0, (winx - 2 * x) / 2, (winy
        - 2 * y) / 2, details);

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
                	if( plateau->lireVue()->getCenter().x  <=  ( (jeu.lirePlateau().getTailleX() + jeu.lirePlateau().getTailleY()/2) * 30 ))
                         plateau->bougerPlateau(5, 0);
                    break;
                case Gauche:
                	if(plateau->lireVue()->getCenter().x >= 0)
                		plateau->bougerPlateau(-5, 0);
                    break;
                case Haut:
                if(plateau->lireVue()->getCenter().y >= 0)
                    plateau->bougerPlateau(0, -5);
                    break;
                case Bas:
                	if( plateau->lireVue()->getCenter().y  <=  ( (jeu.lirePlateau().getTailleY() + jeu.lirePlateau().getTailleX()/2) * 30 ))
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
