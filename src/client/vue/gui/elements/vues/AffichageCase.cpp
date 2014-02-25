/*
 * AffichageCase.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#include "AffichageCase.hpp"

#include <client/Jeu.hpp>
#include <iostream>

AffichageCase::AffichageCase(Gui* gui, int id, float x, float y, float taille,
        Position position, sf::View* vuePlateau) :
        Element(gui, id), image(), fond(), position(position), selectionne(
                false), animation(nullptr) {
    ecrirePosition(x, y);
    ecrireTaille(taille, taille);
    ecrireVue(vuePlateau);

    enregistrerSouris(this);

    fond = sf::CircleShape(taille / 2, 6);
    fond.setPosition(x, y);
    fond.setOrigin(taille / 2, taille / 2);
    fond.setFillColor(sf::Color(0, 0, 110, 60));
    fond.setOutlineThickness(2);
    fond.setOutlineColor(sf::Color(100, 100, 100));

    animation = new Animation(gui, -1, fond.getPosition().x,
            fond.getPosition().y, 200, 200, true, false,
            "Environnement/petite_explosion.png");
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
        image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(
                fichier);
        image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
        Utile::redimensionnerImage(image, lireTaille().x * 1.3,
                lireTaille().y * 1.3, false);
        image.setPosition(lirePosition().x - lireTaille().x * 1.3 / 2,
                lirePosition().y - lireTaille().y * 1.3 / 2);
    }

    // Changement de la couleur de fond
    if (p.getCellule(position).getEstChemin()) {
        // Chemin
        fond.setFillColor(sf::Color(102, 0, 153, 50));
        fond.setOutlineColor(sf::Color(102, 0, 153, 50));
    }
    else if (p.getCellule(position).getEstConstructibleBatiment()) {
        // Constructible bâtiment
        fond.setFillColor(sf::Color(34, 76, 192, 50));
        fond.setOutlineColor(sf::Color(34, 76, 192, 50));
    }
    else if (p.getCellule(position).getParcourable()) {
        // Parcourable
        fond.setFillColor(sf::Color(255, 102, 0, 50));
        fond.setOutlineColor(sf::Color(255, 102, 0, 50));
    }
    else if (p.getCellule(position).getEstAttaquable()) {
        // Attaquable
        fond.setFillColor(sf::Color(204, 0, 0, 50));
        fond.setOutlineColor(sf::Color(204, 0, 0, 50));
    }
    else if (p.getCellule(position).getEstConstructibleVaisseau()) {
        // Constructible vaisseau
        fond.setFillColor(sf::Color(59, 192, 34, 50));
        fond.setOutlineColor(sf::Color(59, 192, 34, 50));
    }
    else if (p.getCellule(position).getEstAttaquee()) {
        animation->lancer();

        p.resetAttaque(position);
    }
    else {
        // Défaut
        fond.setFillColor(sf::Color(150, 150, 150, 50));
        fond.setOutlineColor(sf::Color(150, 150, 150, 50));
    }

    // Changement de la bordure
    if (selectionne)
        // Sélectionnée
        fond.setOutlineColor(sf::Color(204, 0, 0));
    else if (lireSurvol())
        fond.setOutlineColor(sf::Color(255, 204, 0));
    else if (p.getCellule(position).getEstDestination())
        // Destination
        fond.setOutlineColor(sf::Color(51, 51, 255));
}

void AffichageCase::afficher() {
    if (lireGui()->lireScene()->lireJeu().lirePlateau().getCellule(position).getEstVisible()) {
        affichage.draw(image);
    }
    else
    {
        fond.setFillColor(sf::Color(20, 20, 20, 50));
    }

    affichage.draw(fond);
}

bool AffichageCase::contient(sf::Vector2i position) {
    // On teste en x
    bool x = position.x >= fond.getPosition().x - fond.getRadius() * 0.9;
    x &= position.x <= fond.getPosition().x + fond.getRadius() * 0.9;

    // On teste en y
    bool y = position.y >= fond.getPosition().y - fond.getRadius() * 0.9;
    y &= position.y <= fond.getPosition().y + fond.getRadius() * 0.9;

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
    if (!lireGui()->lireScene()->lireJeu().lirePlateau().getCellule(position).getEstVisible())
        return;

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
}

void AffichageCase::entreeSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}

void AffichageCase::sortieSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}

void AffichageCase::moletteSouris(int) {
    /* Ne rien faire ici */
}
