/*
 * AffichageDetails.cpp
 *
 *  Created on: 18 oct. 2013
 *      Author: Soinou
 */

#include "AffichageDetails.hpp"

// Includes de la libstd
#include <sstream>
#include <iostream>

// Includes de nos classes
#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

// Includes des classes utiles
#include <utiles.hpp>

AffichageDetails::AffichageDetails(Gui* gui, int id, float x, float y, float largeur, float hauteur)
: Element(gui, id), fond(), label("", x + 5, y + 5), position(-1, -1) {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    fond.setOrigin(-2, -2);
    fond.setPosition(x, y);
    fond.setSize(sf::Vector2f(largeur - 4, hauteur - 4));
    fond.setFillColor(sf::Color(50, 50, 50));
    fond.setOutlineColor(sf::Color(100, 100, 100));
    fond.setOutlineThickness(2);

    label.setFont(lireGui()->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
}

AffichageDetails::~AffichageDetails() {

}

void AffichageDetails::actualiser(float) {
    if (position.x == -1 && position.y == -1)
    {
        label.setString(std::wstring(L"Aucune case n'est selectionée"));

        return;
    }

    Plateau p = lireGui()->lireScene()->lireJeu().lirePlateau();
    TypeCellule cellule = p.getCellule(position).statutEmplacement();
    std::wstring texte;

    switch (cellule) {
    case TypeCellule::Vaisseau:
        texte = Utile::toString(p.getVaisseau(position));
        break;
    case TypeCellule::Batiment:
        texte = Utile::toString(p.getBatiment(position));
        break;
    case TypeCellule::Evenement:
        texte = Utile::toString(p.getEvenement(position));
        break;
    default:
        texte = Utile::toString(position);
        break;
    }

    label.setString(texte);
}

void AffichageDetails::afficher(sf::RenderWindow& affichage) {
    affichage.draw(fond);
    affichage.draw(label);
}

bool AffichageDetails::contient(sf::Vector2i) {
    return false;
}

void AffichageDetails::selectionner(int i, int j) {
    position = Position(i, j);
}

void AffichageDetails::selectionner(Position position) {
    this->position = position;
}

void AffichageDetails::selectionner() {
    position = Position(-1, -1);
}

bool AffichageDetails::estSelectionne() {
    return position.x != -1 && position.y != -1;
}

Position AffichageDetails::lirePosition() {
    return position;
}
