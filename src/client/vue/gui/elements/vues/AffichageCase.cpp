/*
 * AffichageCase.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#include "AffichageCase.hpp"

#include <client/Jeu.hpp>
#include <iostream>

AffichageCase::AffichageCase(Gui* gui, int id, float x, float y, float taille, Position position, sf::View* vuePlateau)
                : Element(gui, id), image(), fond(), position(position), selectionne(false) {
    ecrirePosition(x, y);
    ecrireTaille(taille, taille);
    ecrireVue(vuePlateau);

    enregistrerSouris(ObservateurSouris::Ptr(this));

    fond = sf::CircleShape(taille / 2, 6);
    fond.setPosition(x + taille / 2, y + taille / 2);
    fond.setOrigin(taille / 2, taille / 2);
    fond.setFillColor(sf::Color(0, 0, 0, 0));
    fond.setOutlineColor(sf::Color(255, 255, 255));
    fond.setOutlineThickness(2);
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
        case TypeCellule::Vaisseau: {
            DetailVaisseau vaisseau = p.getVaisseau(position);

            fichier = Utile::lireFichier(vaisseau.type);
            break;
        }
        case TypeCellule::Batiment: {
            DetailBatiment batiment = p.getBatiment(position);

            fichier = Utile::lireFichier(batiment.type);
            break;
        }
        case TypeCellule::Evenement: {
            DetailEvenement evenement = p.getEvenement(position);

            fichier = Utile::lireFichier(evenement.type);
            break;
        }
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
        Utile::redimensionnerImage(image, lireTaille().x, lireTaille().y, false);
    }

    // Selon que la case soit selectionnée, survolée, ou rien du tout, on change la couleur de la bordure
    if (selectionne)
        fond.setOutlineColor(sf::Color(255, 255, 0));
    else if (lireSurvol())
        fond.setOutlineColor(sf::Color(255, 0, 0));
    else
        fond.setOutlineColor(sf::Color(255, 255, 255));

    if (p.getCellule(position).getParcourable())
        fond.setFillColor(sf::Color(0, 255, 0));
    else
        fond.setFillColor(sf::Color(0, 0, 0, 0));
}

void AffichageCase::afficher(sf::RenderWindow& affichage) {
    affichage.draw(fond);
    affichage.draw(image);
}

bool AffichageCase::contient(sf::Vector2i position) {
    return position.x >= fond.getPosition().x - fond.getRadius() * 0.9 && position.x <= fond.getPosition().x + fond.getRadius() * 0.9 && position.y >= fond.getPosition().y - fond.getRadius() * 0.9 && position.y <= fond.getPosition().y + fond.getRadius() * 0.9;
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

void AffichageCase::clicSouris() {
    if (!selectionne) {
        selectionne = true;

        envoyerMessage();
    }
}

void AffichageCase::pressionSouris(sf::Mouse::Button) {

}

void AffichageCase::relachementSouris(sf::Mouse::Button) {
    if (!lireSurvol() && selectionne) {
        selectionne = false;
    }
}

void AffichageCase::entreeSouris(sf::Vector2f) {

}

void AffichageCase::sortieSouris(sf::Vector2f) {

}

void AffichageCase::moletteSouris(int) {

}
