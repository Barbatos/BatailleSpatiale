/*
 * LigneServeur.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#include "LigneServeur.hpp"

LigneServeur::LigneServeur(Gui* gui, int id, int x, int y, int largeur, int hauteur,
    Serveur* serveur)
                : Element(gui, id), serveur(serveur), bouton(), texteBouton(), cadre(), texteCadre() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    cadre.setPosition(x, y);
    cadre.setSize(sf::Vector2f(largeur, hauteur));
    cadre.setOutlineThickness(2);
    cadre.setFillColor(sf::Color(0, 0, 0, 50));
    cadre.setOutlineColor(sf::Color(255, 255, 255));

    texteCadre.setFont(gui->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
    texteCadre.setCharacterSize(12);
    texteCadre.setPosition(x + 5, y + texteCadre.getCharacterSize() / 2);

    bouton.setPosition(x + 4 * largeur / 5 - 5, y + 5);
    bouton.setSize(sf::Vector2f(largeur / 5 - 5, hauteur - 10));
    bouton.setOutlineThickness(2);
    bouton.setFillColor(sf::Color(0, 0, 0, 50));
    bouton.setOutlineColor(sf::Color(255, 255, 255));

    texteBouton.setFont(gui->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
    texteBouton.setCharacterSize(12);
    texteBouton.setPosition(x + 4 * largeur / 5, y + 5 + texteBouton.getCharacterSize() / 2);
    texteBouton.setString("Connecter");
}

LigneServeur::~LigneServeur() {
}

void LigneServeur::actualiser(float) {

}

void LigneServeur::afficher() {
    affichage.draw(cadre);
    affichage.draw(bouton);
    affichage.draw(texteCadre);
}

bool LigneServeur::contient(sf::Vector2i position) {
    return bouton.getGlobalBounds().contains(sf::Vector2f(position));
}

void LigneServeur::clicSouris(bool clicDroit) {
    if (clicDroit)
        return;
}

void LigneServeur::pressionSouris(sf::Mouse::Button) {

}

void LigneServeur::relachementSouris(sf::Mouse::Button) {

}

void LigneServeur::entreeSouris(sf::Vector2f) {

}

void LigneServeur::sortieSouris(sf::Vector2f) {

}

void LigneServeur::moletteSouris(int) {

}
