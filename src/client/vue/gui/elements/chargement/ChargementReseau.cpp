/*
 * ChargementJeu.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "ChargementReseau.hpp"

#include <client/Jeu.hpp>

ChargementReseau::ChargementReseau(Gui* gui, int id, int x, int y, int largeur, int hauteur)
                : Element(gui, id),
                  texte(),
                  image(gui, -1, x, y, largeur, hauteur - texte.getCharacterSize() - 5, true, "Interface/chargement.png") {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    texte.setString("Chargement du reseau en cours ...");
    texte.setFont(gui->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
    texte.setPosition(x + (largeur - texte.getGlobalBounds().width) / 2, y + (hauteur - texte.getCharacterSize()));
}

ChargementReseau::~ChargementReseau() {
}

void ChargementReseau::actualiser(float) {
    if (lireGui()->lireScene()->lireJeu().lireReseau()->getActif() && lireGui()->lireScene()->lireJeu().lirePlateau().getTailleX() != 0) {
        Message message;

        message.type = Message::Element;

        message.element.clic = true;
        message.element.id = lireId();

        envoyerMessage(message);
    }
}

void ChargementReseau::afficher(sf::RenderWindow& fenetre) {
    fenetre.draw(texte);
}

bool ChargementReseau::contient(sf::Vector2i) {
    return false;
}
