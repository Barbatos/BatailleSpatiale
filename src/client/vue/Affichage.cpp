/*
 * Affichage.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Affichage.hpp"

#define TITRE_FENETRE "BattleStar2.0"
#define HAUTEUR_FENETRE 1200
#define LARGEUR_FENETRE 675

Affichage::Affichage() :
		sf::RenderWindow()
{

}

Affichage::~Affichage()
{

}

void Affichage::creer()
{
	create(sf::VideoMode::getFullscreenModes()[0], TITRE_FENETRE,
			sf::Style::Fullscreen);

	setVerticalSyncEnabled(true);
}
