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

    enregistrerSouris(ObservateurSouris::Ptr(this));

    fond = sf::CircleShape(taille / 1.6, 6);
    fond.setPosition(x + taille / 2, y + taille / 2);
    fond.setOrigin(taille / 2, taille / 2);
    fond.setFillColor(sf::Color(0, 0, 110, 60));
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
        Utile::redimensionnerImage(image, lireTaille().x * 1.2, lireTaille().y * 1.2, true);
    }

    // Selon que la case soit selectionnée, survolée, ou rien du tout, on change la couleur de la bordure
    if (selectionne)
        fond.setFillColor(sf::Color(255, 255, 0, 60));
    else if (lireSurvol())
        fond.setFillColor(sf::Color(255, 0, 0, 60));
    else if (p.getCellule(position).getParcourable())
        fond.setFillColor(sf::Color(92, 185, 188, 60));
    else
        fond.setFillColor(sf::Color(0, 0, 110, 60));
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

void AffichageCase::clicSouris(bool clicDroit) {
    if (!selectionne) {
        selectionne = true;

        Message message;

        message.type = Message::Cellule;
        message.cellule.x = position.x;
        message.cellule.y = position.y;
        message.cellule.selection = true;
        message.cellule.clicDroit = clicDroit;

        envoyerMessage(message);
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
