/*
 * ListeServeurs.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#include "ListeServeurs.hpp"

#include "LigneServeur.hpp"

#include <iostream>

#include <client/modele/Serveur.hpp>

ListeServeurs::ListeServeurs(Gui* gui, int id, int x, int y, int largeur,
        int hauteur) :
        Element(gui, id), lignes(), vue() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    vue.setViewport(sf::FloatRect(0, 0, 1, 1));

    const std::vector<Serveur>& liste =
            gui->lireScene()->lireJeu().lirePlateau().getServeurs();

    int dy = 0;
    for (std::vector<Serveur>::size_type i = 0; i < liste.size(); i++) {
        dy = i * 40 + affichage.getSize().y / 15;

        lignes.push_back(new LigneServeur(gui, i, affichage.getSize().x / 4, dy, affichage.getSize().x / 2, 30, liste[i], &vue));
    }

    vue.setSize(sf::Vector2f(affichage.getSize().x, affichage.getSize().y));

    vue.zoom(1.5f);
}

ListeServeurs::~ListeServeurs() {
}

void ListeServeurs::actualiser(float) {
    if (lireGui()->lireScene()->lireJeu().lireReseau()->getActif()) {
        Message message;

        message.type = Message::Element;
        message.element.id = lireId();
        message.element.clic = false;

        envoyerMessage(message);
    }
}

void ListeServeurs::afficher() {

}

bool ListeServeurs::contient(sf::Vector2i) {
    return false;
}
