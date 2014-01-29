/*
 * BarreMesure.cpp
 *
 *  Created on: 29 janv. 2014
 *      Author: Tahiry
 */

#include "BarreMesure.hpp"

BarreMesure::BarreMesure(Gui* gui, std::string texte, float x, float y, float largeur,
		float hauteur) :
		Element(gui,-1), contour(), progression(), description() {

	Joueur* joueur = lireGui()->lireScene()->lireJeu().lireJoueur();
	coefficient = largeur/joueur->getCommandement();

	contour.setOrigin(-2,-2);
	contour.setSize(sf::Vector2f(largeur,hauteur));
	contour.setFillColor(sf::Color(255,255,255));
	contour.setOutlineColor(sf::Color(150,150,150));
	contour.setOutlineThickness(2);
	contour.setPosition(x-contour.getSize().x-10, y+10);

	progression.setOrigin(-2,-2);
	progression.setSize(sf::Vector2f(joueur->getCommandement()*coefficient,hauteur));
	progression.setFillColor(sf::Color(100,100,255));
	progression.setPosition(x-progression.getSize().x-10, y+10);

	description.setFont(lireGui()->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
	description.setString(texte);
	description.setPosition(contour.getPosition().x,contour.getPosition().y+20);
}

BarreMesure::~BarreMesure() {

}

void BarreMesure::actualiser(float) {

}

void BarreMesure::afficher(sf::RenderWindow& affichage) {
    affichage.draw(contour);
    affichage.draw(progression);
    affichage.draw(description);
}

bool BarreMesure::contient(sf::Vector2i) {
    return false;
}

