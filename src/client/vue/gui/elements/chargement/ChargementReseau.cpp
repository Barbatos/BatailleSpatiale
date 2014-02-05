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
                  texteReseau(),
                  texteJoueurs(),
                  image(gui, -1, x, y, largeur, hauteur - texteReseau.getCharacterSize() - 5, true, true, "Interface/chargement.png"),
                  reseauActif(false) {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    texteReseau.setString("Chargement du reseau en cours...");
    texteReseau.setFont(gui->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
    texteReseau.setPosition(x + (largeur - texteReseau.getGlobalBounds().width) / 2, y + (hauteur - texteReseau.getCharacterSize()));

    texteJoueurs.setString("En attente d'un joueur adverse...");
    texteJoueurs.setFont(gui->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
    texteJoueurs.setPosition(x + (largeur - texteJoueurs.getGlobalBounds().width) / 2, y + (hauteur - texteJoueurs.getCharacterSize()));
}

ChargementReseau::~ChargementReseau() {
}

void ChargementReseau::actualiser(float) {
    if (!reseauActif && lireGui()->lireScene()->lireJeu().lireReseau()->getActif() && lireGui()->lireScene()->lireJeu().lirePlateau().getTailleX() != 0) {
        setReseauActif(true);
    }

    if(reseauActif && 
        (lireGui()->lireScene()->lireJeu().lireReseau()->getPartieActive() || 
        lireGui()->lireScene()->lireJeu().lireReseau()->getPartieSolo())) {
        Message message;

        message.type = Message::Element;

        message.element.clic = true;
        message.element.id = lireId();

        envoyerMessage(message);
    }
}

void ChargementReseau::afficher(sf::RenderWindow& fenetre) {
    if(reseauActif) {
        fenetre.draw(texteJoueurs);
    }
    else {
        fenetre.draw(texteReseau);
    }
}

bool ChargementReseau::contient(sf::Vector2i) {
    return false;
}

void ChargementReseau::setReseauActif(bool _actif) {
    reseauActif = _actif;
}
