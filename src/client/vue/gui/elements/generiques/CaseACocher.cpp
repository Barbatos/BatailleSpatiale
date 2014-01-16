/*
 * CaseACocher.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Tahiry
 */

#include "CaseACocher.hpp"
#include <client/vue/gui/Element.hpp>
#include <client/vue/Affichage.hpp>

/**
 * @brief Constructeur de l'objet
 */
CaseACocher::CaseACocher(Gui* gui, int id, int x, int y, float hauteur,
                         float largeur) :
	Element(gui, id), boite(), clique(false) {
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	//creation de l'�l�ment
	sf::Vector2f size = sf::Vector2f(hauteur, largeur);
	boite.setSize(size);
}

/**
 * Destructeur de l'objet
 */
CaseACocher::~CaseACocher() {

}

void CaseACocher::actualiser(float) {

}

void CaseACocher::afficher(sf::RenderWindow& affichage) {
	affichage.draw(boite);
}

bool CaseACocher::contient(sf::Vector2i position) {
	return boite.getGlobalBounds().contains(position.x, position.y);
}

bool CaseACocher::estCoche() {
	return clique;
}

void CaseACocher::clicSouris() {
	if (boite.getFillColor() == sf::Color::Cyan) {
		clique = false;
		boite.setFillColor(sf::Color::White);
	} else {
		clique = true;
		boite.setFillColor(sf::Color::Cyan);
	}
}
void CaseACocher::pressionSouris(sf::Mouse::Button) {

}

void CaseACocher::relachementSouris(sf::Mouse::Button) {

}

void CaseACocher::entreeSouris(sf::Vector2f) {
	sf::Color color(120, 120, 120);
	boite.setFillColor(color);
}

void CaseACocher::sortieSouris(sf::Vector2f) {

}

void CaseACocher::moletteSouris(int) {

}
