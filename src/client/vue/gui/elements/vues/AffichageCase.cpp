/*
 * AffichageCase.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#include "AffichageCase.hpp"

#include <client/Jeu.hpp>
#include <iostream>

AffichageCase::AffichageCase(Gui* gui, int id, float x, float y, float taille, Position position,
    sf::View* vuePlateau)
                : Element(gui, id), image(), fond(), position(position), selectionne(false) {
    ecrirePosition(x, y);
    ecrireTaille(taille, taille);
    ecrireVue(vuePlateau);

    enregistrerSouris(this);

    fond = sf::CircleShape(taille / 1.6, 6);
    fond.setPosition(x + taille / 2, y + taille / 2);
    fond.setOrigin(taille / 2, taille / 2);
    fond.setFillColor(sf::Color(0, 0, 110, 60));
    fond.setOutlineThickness(0.5f);
    fond.setOutlineColor(sf::Color(100, 100, 100, 40));
}

AffichageCase::~AffichageCase() {
}

void AffichageCase::actualiser(float) {
    // On stocke le plateau dans une variable temporaire
    Plateau& p = lireGui()->lireScene()->lireJeu().lirePlateau();

    // On stocke le type de la cellule
    TypeCellule cellule = p.getCellule(position).statutEmplacement();

    // On créé une variable string pour stocker le chemin vers l'image
    std::string fichier = "";

    // On change l'image selon ce type
    switch (cellule) {
        case TypeCellule::Vaisseau:
            fichier = Utile::lireFichier(p.getVaisseau(position));
            break;

        case TypeCellule::Batiment:
            fichier = Utile::lireFichier(p.getBatiment(position));
            break;

        case TypeCellule::Evenement:
            fichier = Utile::lireFichier(p.getEvenement(position));
            break;

        default:
            break;
    }

    if (fichier == "")
        image = sf::Sprite();
    else {
        // On met l'image du vaisseau correspondant
        image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(fichier);
        image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
        image.setPosition(lirePosition().x, lirePosition().y);
        Utile::redimensionnerImage(image, lireTaille().x * 1.2, lireTaille().y * 1.2, true);
    }

    // Selon que la case soit selectionnée, survolée, ou rien du tout, on change la couleur de la bordure
    if (selectionne)
        fond.setFillColor(sf::Color(255, 0, 0, 60));
    else if (lireSurvol())
        fond.setFillColor(sf::Color(255, 255, 0, 60));
    else if (p.getCellule(position).getEstChemin())
        fond.setFillColor(sf::Color(153, 0, 51, 60));
    else if (p.getCellule(position).getParcourable())
        fond.setFillColor(sf::Color(102, 153, 102, 60));
    else
        fond.setFillColor(sf::Color(0, 0, 110, 60));
}

void AffichageCase::afficher(sf::RenderWindow& affichage) {
    //affichage.draw(contour);
    affichage.draw(fond);
    affichage.draw(image);
}

bool AffichageCase::contient(sf::Vector2i position) {
    // On teste en x
    bool x = position.x >= fond.getPosition().x - fond.getRadius() * 0.6;
    x &= position.x <= fond.getPosition().x + fond.getRadius();

    // On teste en y
    bool y = position.y >= fond.getPosition().y - fond.getRadius() * 0.6;
    y &= position.y <= fond.getPosition().y + fond.getRadius();

    // On retourne le résultat
    return x && y;
}

Position AffichageCase::lirePositionPlateau() {
    return position;
}

bool AffichageCase::lireSelectionne() {
    return selectionne;
}

void AffichageCase::ecrirePositionPlateau(Position position) {
    this->position = position;
}

void AffichageCase::clicSouris(bool clicDroit) {
    if (clicDroit) {
        Message message;

        message.type = Message::Cellule;

        message.cellule.x = position.x;
        message.cellule.y = position.y;
        message.cellule.selection = false;
        message.cellule.clicDroit = true;

        envoyerMessage(message);
    }
    else {
        Message message;

        message.type = Message::Cellule;

        message.cellule.x = position.x;
        message.cellule.y = position.y;

        if (!selectionne) {
            selectionne = true;
            message.cellule.selection = true;
        }
        else
            message.cellule.selection = false;

        message.cellule.clicDroit = false;

        envoyerMessage(message);
    }

}

void AffichageCase::pressionSouris(sf::Mouse::Button) {

}

void AffichageCase::relachementSouris(sf::Mouse::Button bouton) {

    if (!lireSurvol() && selectionne && bouton == sf::Mouse::Left)
        selectionne = false;
    /*
     Message message;

     message.type = Message::Cellule;

     message.cellule.x = position.x;
     message.cellule.y = position.y;
     message.cellule.selection = false;
     message.cellule.clicDroit = false;

     envoyerMessage(message);
     } */
}

void AffichageCase::entreeSouris(sf::Vector2f) {

}

void AffichageCase::sortieSouris(sf::Vector2f) {

}

void AffichageCase::moletteSouris(int) {

}
