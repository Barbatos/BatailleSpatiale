/*
 * TexteFinDeJeu.cpp
 *
 *  Created on: 26 févr. 2014
 *      Author: Soinou
 */

#include "TexteFinDeJeu.hpp"

#include <client/vue/Affichage.hpp>

TexteFinDeJeu::TexteFinDeJeu(Gui* gui, int id, int x, int y) :
        Element(gui, id), texte() {
    texte.setString(L"La partie est terminée !");
    texte.setFont(
            gui->lireScene()->lireJeu().lireRessources().lirePolice(
                    "grand9k.ttf"));
    texte.setCharacterSize(30);
    texte.setPosition(x - texte.getGlobalBounds().width / 2,
            y - texte.getCharacterSize() / 2);
}

TexteFinDeJeu::~TexteFinDeJeu() {
}

void TexteFinDeJeu::actualiser(float) {

}

void TexteFinDeJeu::afficher() {
    affichage.draw(texte);
}

bool TexteFinDeJeu::contient(sf::Vector2i) {
    return false;
}
