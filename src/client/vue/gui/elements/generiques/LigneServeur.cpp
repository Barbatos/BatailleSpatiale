/*
 * LigneServeur.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#include "LigneServeur.hpp"

LigneServeur::LigneServeur(Gui* gui, int id, int x, int y, int largeur,
        int hauteur, const Serveur& serveur, sf::View*) :
        Element(gui, id), serveur(serveur), bouton(), texteBouton(), cadre(), texteCadre() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);
    enregistrerSouris(this);
    //ecrireVue(vue);

    cadre.setPosition(x, y);
    cadre.setSize(sf::Vector2f(largeur, hauteur));
    cadre.setOutlineThickness(2);
    cadre.setFillColor(sf::Color(0, 0, 0));
    cadre.setOutlineColor(sf::Color(100, 100, 100));

    std::stringstream stream;

    stream << serveur.getNom() << " : " << serveur.getPort();

    texteCadre.setFont(
            gui->lireScene()->lireJeu().lireRessources().lirePolice(
                    "grand9k.ttf"));
    texteCadre.setCharacterSize(12);
    texteCadre.setString(stream.str());
    texteCadre.setPosition(x + 5, y + texteCadre.getCharacterSize() / 2);

    bouton.setPosition(x + 4 * largeur / 5, y + 5);
    bouton.setSize(sf::Vector2f(largeur / 5 - 5, hauteur - 10));
    bouton.setOutlineThickness(2);
    bouton.setFillColor(sf::Color(20, 20, 20));
    bouton.setOutlineColor(sf::Color(100, 100, 100));

    texteBouton.setFont(
            gui->lireScene()->lireJeu().lireRessources().lirePolice(
                    "grand9k.ttf"));
    texteBouton.setCharacterSize(12);
    texteBouton.setString("Connecter");
    texteBouton.setPosition(
            x + 4 * largeur / 5
                    + (bouton.getSize().x - texteBouton.getGlobalBounds().width)
                            / 2, y + texteBouton.getCharacterSize() / 2);

}

LigneServeur::~LigneServeur() {
}

void LigneServeur::actualiser(float) {
    if (lireAppui()) {
        bouton.setFillColor(sf::Color(100, 100, 20));
    }
    else if (lireSurvol()) {
        bouton.setFillColor(sf::Color(100, 20, 20));
    }
    else {
        bouton.setFillColor(sf::Color(20, 20, 20));
    }
}

void LigneServeur::afficher() {
    affichage.draw(cadre);
    affichage.draw(bouton);
    affichage.draw(texteCadre);
    affichage.draw(texteBouton);
}

bool LigneServeur::contient(sf::Vector2i position) {
    return bouton.getGlobalBounds().contains(sf::Vector2f(position));
}

void LigneServeur::clicSouris(bool clicDroit) {
    if (clicDroit)
        return;

    lireGui()->lireScene()->lireJeu().lireRessources().jouerSon(
            "menuclick.wav");

    lireGui()->lireScene()->lireJeu().lireReseau()->ConnexionServeur(
            serveur.getIp(), serveur.getPort(), false);
}

void LigneServeur::pressionSouris(sf::Mouse::Button) {

}

void LigneServeur::relachementSouris(sf::Mouse::Button) {

}

void LigneServeur::entreeSouris(sf::Vector2f) {
    lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuhit.wav");
}

void LigneServeur::sortieSouris(sf::Vector2f) {

}

void LigneServeur::moletteSouris(int) {

}
