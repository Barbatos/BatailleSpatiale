/*
 * Bouton.cpp
 *
 *  Created on: 5 oct. 2013
 *      Author: Tendry
 */

#include "Bouton.hpp"

Bouton::Bouton(Gui* gui, int id, std::string texte, float x, float y, float largeur, float hauteur)
                : Element(gui, id), ObservateurSouris(), label(texte, x, y) {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    enregistrerSouris(this);

    normal = lireGui()->lireScene()->lireJeu().lireRessources().lireImage("Interface/Bouton/bouton.png");
    survol = lireGui()->lireScene()->lireJeu().lireRessources().lireImage("Interface/Bouton/bouton_dessus.png");
    appui = lireGui()->lireScene()->lireJeu().lireRessources().lireImage("Interface/Bouton/bouton_clic.png");

    Utile::redimensionnerImage(normal, lireTaille().x, lireTaille().y, false);
    normal.setPosition(lirePosition().x, lirePosition().y);
    Utile::redimensionnerImage(survol, lireTaille().x, lireTaille().y, false);
    survol.setPosition(lirePosition().x, lirePosition().y);
    Utile::redimensionnerImage(appui, lireTaille().x, lireTaille().y, false);
    appui.setPosition(lirePosition().x, lirePosition().y);

    ecrireZone(normal.getGlobalBounds());

    label.setFont(lireGui()->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));

    label.setOrigin(-(lireTaille().x - label.getGlobalBounds().width) / 2, -(lireTaille().y
                    - label.getGlobalBounds().height) / 2);
}

Bouton::~Bouton() {

}

std::string Bouton::lireTexte() {
    return label.getString();
}

void Bouton::ecrireTexte(std::wstring texte) {
    label.setString(texte);

    label.setOrigin(-(lireTaille().x - label.getGlobalBounds().width) / 2, -(lireTaille().y
                    - label.getGlobalBounds().height) / 2);
}

void Bouton::ecrireTexte(std::string texte) {
    label.setString(texte);

    label.setOrigin(-(lireTaille().x - label.getGlobalBounds().width) / 2, -(lireTaille().y
                    - label.getGlobalBounds().height) / 2);
}

void Bouton::actualiser(float) {

}

void Bouton::afficher() {
    if (lireAppui())
        affichage.draw(appui);
    else if (lireSurvol())
        affichage.draw(survol);
    else
        affichage.draw(normal);

    affichage.draw(label);
}

bool Bouton::contient(sf::Vector2i position) {
    return normal.getGlobalBounds().contains(position.x, position.y);
}

void Bouton::clicSouris(bool clicDroit) {
    if (!clicDroit) {
        lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuclick.wav");

        Message message;

        message.type = Message::Element;
        message.element.clic = true;
        message.element.id = lireId();

        envoyerMessage(message);
    }
}

void Bouton::pressionSouris(sf::Mouse::Button) {

}

void Bouton::relachementSouris(sf::Mouse::Button) {

}

void Bouton::entreeSouris(sf::Vector2f) {
    lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuhit.wav");
}

void Bouton::sortieSouris(sf::Vector2f) {

}

void Bouton::moletteSouris(int) {

}

void Bouton::changerPosition(float x, float y)
{
	ecrirePosition(x,y);
	normal.setPosition(lirePosition().x, lirePosition().y);
	survol.setPosition(lirePosition().x, lirePosition().y);
	appui.setPosition(lirePosition().x, lirePosition().y);
	label.setPosition(lirePosition().x, lirePosition().y);
}
