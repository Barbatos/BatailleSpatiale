/*
 * Affichage.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Affichage.hpp"

Affichage* Affichage::instance = nullptr;

Affichage::Affichage() :
		sf::RenderWindow() {

}

Affichage::~Affichage() {

}

void Affichage::initialiser() {
	instance = new Affichage();
}

void Affichage::detruire() {
	delete instance;
}

void Affichage::creer() {
	create(sf::VideoMode::getFullscreenModes()[0], "BattleStar2.0",
			sf::Style::Fullscreen);

	setFramerateLimit(60);
}

void Affichage::creer(sf::VideoMode mode, std::string titre, sf::Int32 style) {
	create(mode, titre, style);

	setFramerateLimit(60);
}

Affichage& Affichage::lireInstance() {
	return *instance;
}
