/*
 * BoutonDeplacementPlateau.cpp
 *
 *  Created on: 5 d�c. 2013
 *      Author: Thornydre
 */

#include "BoutonDeplacementPlateau.hpp"

// Includes des classes pré-déclarées et/ou dont on a besoin
#include <client/utile/Utile.hpp>
#include <client/Jeu.hpp>

// Includes de la libstd
#include <iostream>

BoutonDeplacementPlateau::BoutonDeplacementPlateau(Gui* gui, int id, float x, float y,
    float largeur, float hauteur)
                : Element(gui, id), ObservateurSouris(), fond() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    enregistrerSouris(ObservateurSouris::Ptr(this));

    fond.setPosition(x, y);
    fond.setSize(sf::Vector2f(largeur, hauteur));
    fond.setFillColor(sf::Color(50, 50, 50, 150));
}

BoutonDeplacementPlateau::~BoutonDeplacementPlateau() {

}

void BoutonDeplacementPlateau::actualiser(float) {
    if (lireSurvol()) {
        Message message;

        message.type = Message::Element;

        message.element.id = lireId();
        message.element.clic = true;

        envoyerMessage(message);
    }
}

void BoutonDeplacementPlateau::afficher(sf::RenderWindow& affichage) {
    affichage.draw(fond);
}

bool BoutonDeplacementPlateau::contient(sf::Vector2i position) {
    return fond.getGlobalBounds().contains(position.x, position.y);
}

void BoutonDeplacementPlateau::clicSouris(bool) {

}
void BoutonDeplacementPlateau::pressionSouris(sf::Mouse::Button) {

}

void BoutonDeplacementPlateau::relachementSouris(sf::Mouse::Button) {

}

void BoutonDeplacementPlateau::entreeSouris(sf::Vector2f) {
    fond.setFillColor(sf::Color(50, 50, 50, 200));

    lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuhit.wav");

    Message message;

    message.type = Message::Element;

    message.element.id = lireId();
    message.element.clic = true;

    envoyerMessage(message);
}

void BoutonDeplacementPlateau::sortieSouris(sf::Vector2f) {
    fond.setFillColor(sf::Color(50, 50, 50, 150));
}

void BoutonDeplacementPlateau::moletteSouris(int) {

}
