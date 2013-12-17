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
	create(sf::VideoMode(HAUTEUR_FENETRE, LARGEUR_FENETRE), TITRE_FENETRE,
			sf::Style::Close);

	setVerticalSyncEnabled(true);
}

Affichage::~Affichage()
{

}
