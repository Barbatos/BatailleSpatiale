/*
 * ChargementReseau.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "ChargementReseau.hpp"

ChargementReseau::ChargementReseau(Gui* gui, int id) :
		Element(gui, id)
{

}

ChargementReseau::~ChargementReseau()
{
}

void ChargementReseau::actualiser(float)
{
	if (lireGui()->lireScene()->lireJeu().lireReseau()->getActif() && lireGui()
			->lireScene()->lireJeu().lirePlateau().getTailleX() != 0)
		envoyerMessage();
}

void ChargementReseau::afficher(sf::RenderWindow&)
{

}

bool ChargementReseau::contient(sf::Vector2i)
{
	return false;
}
