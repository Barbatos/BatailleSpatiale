/*
 * BoutonConstruction.cpp
 *
 *  Created on: 24 févr. 2014
 *      Author: Soinou
 */

#include "BoutonConstruction.hpp"

BoutonConstruction::BoutonConstruction(Gui* gui, int id, int x, int y,
        int largeur, int hauteur) :
        Element(gui, id), cadre(), image(), type(TypeCellule::Vide) {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    enregistrerSouris(this);

    cadre.setPosition(x, y);
    cadre.setSize(sf::Vector2f(largeur, hauteur));
    cadre.setFillColor(sf::Color(50, 50, 50));
    cadre.setOutlineColor(sf::Color(0, 0, 0));
    cadre.setOutlineThickness(2);
}

BoutonConstruction::~BoutonConstruction() {
}

void BoutonConstruction::actualiser(float) {
    if (lireAppui()) {
        cadre.setFillColor(sf::Color(100, 100, 20));
    }
    else if (lireSurvol()) {
        cadre.setFillColor(sf::Color(100, 20, 20));
    }
    else {
        cadre.setFillColor(sf::Color(20, 20, 20));
    }
}

void BoutonConstruction::afficher() {
    affichage.draw(cadre);
    affichage.draw(image);
}

bool BoutonConstruction::contient(sf::Vector2i position) {
    return cadre.getGlobalBounds().contains(sf::Vector2f(position));
}

TypeCellule BoutonConstruction::lireType() {
    return type;
}

void BoutonConstruction::ecrireType(TypeVaisseau type) {
    this->type = TypeCellule::Vaisseau;

    this->vaisseau = type;

    image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(
            Utile::lireFichier(type, 1));
    image.setTextureRect(sf::IntRect(0, 0, 480, 480));
    image.setPosition(lirePosition().x, lirePosition().y);

    Utile::redimensionnerImage(image, lireTaille().x, lireTaille().y, false);
}

void BoutonConstruction::ecrireType(TypeBatiment type) {
    this->type = TypeCellule::Batiment;

    this->batiment = type;

    image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(
            Utile::lireFichier(type, 1));
    image.setTextureRect(sf::IntRect(0, 0, 480, 480));
    image.setPosition(lirePosition().x, lirePosition().y);

    Utile::redimensionnerImage(image, lireTaille().x, lireTaille().y, false);
}

TypeVaisseau BoutonConstruction::lireVaisseau() {
    return vaisseau;
}

TypeBatiment BoutonConstruction::lireBatiment() {
    return batiment;
}

void BoutonConstruction::clicSouris(bool clicDroit) {
    if (!clicDroit) {
        Message message;

        message.type = Message::Construction;

        message.construction.type = type;

        switch (type) {
            case TypeCellule::Vaisseau:
                message.construction.vaisseau = vaisseau;
                break;
            case TypeCellule::Batiment:
                message.construction.batiment = batiment;
                break;
            default:
                break;
        }

        envoyerMessage(message);
    }
}

void BoutonConstruction::pressionSouris(sf::Mouse::Button) {

}

void BoutonConstruction::relachementSouris(sf::Mouse::Button) {

}

void BoutonConstruction::entreeSouris(sf::Vector2f) {

}

void BoutonConstruction::sortieSouris(sf::Vector2f) {

}

void BoutonConstruction::moletteSouris(int) {

}
