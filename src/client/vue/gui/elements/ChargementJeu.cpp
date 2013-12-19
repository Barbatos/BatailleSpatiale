/*
 * ChargementJeu.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "ChargementJeu.hpp"

ChargementJeu::ChargementJeu(Gui* gui, int id) :
		Element(gui, id)
{

}

ChargementJeu::~ChargementJeu()
{
}

void ChargementJeu::actualiser(float)
{
	if (lireGui()->lireScene()->lireJeu().lireReseau()->getActif() && lireGui()
			->lireScene()->lireJeu().lirePlateau().getTailleX() != 0)
		envoyerMessage();
}

void ChargementJeu::afficher(sf::RenderWindow&)
{

}

bool ChargementJeu::contient(sf::Vector2i)
{
	return false;
}
