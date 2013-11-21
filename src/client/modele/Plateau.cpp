/*
 * Plateau.cpp
 *
 *  Created on: 11 nov. 2013
 *      Author: Soinou
 */

#include "Plateau.hpp"

Plateau::Plateau() :
		xVaisseau(0),
		yVaisseau(0)
{

}

Plateau::~Plateau()
{
}

bool Plateau::possedeBatiment(Position p)
{
	return false;
}

bool Plateau::possedeVaisseau(Position p)
{
	if (p.x == xVaisseau && p.y == yVaisseau)
		return true;
	else
		return false;
}

bool Plateau::possedeEvenement(Position p)
{
	return false;
}

DetailVaisseau Plateau::getVaisseau(Position p)
{

	if (p.x == xVaisseau && p.y == yVaisseau)
	{
		DetailVaisseau vaisseau = ((DetailVaisseau ) {
					TypeVaisseau::Simple, 45, 50, 50, 100, 50, 5, 5, 9000, 42, 5 } );

		return vaisseau;
	}
	else
	{
		DetailVaisseau vaisseau = ((DetailVaisseau ) {
					TypeVaisseau::Inexistant, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } );

		return vaisseau;
	}
}

DetailBatiment Plateau::getBatiment(Position p)
{
	DetailBatiment batiment = ((DetailBatiment ) {
				TypeBatiment::Inexistant, 0, 0, 0, 0, 0, 0, 0, 0, 0 } );

	return batiment;
}

DetailEvenement Plateau::getEvenement(Position p)
{

	DetailEvenement evenement = ((DetailEvenement ) {
				TypeEvenement::Inexistant, 0, 0, 0, 0 } );

	return evenement;
}

sf::Int16 Plateau::getTailleX()
{
	return 10;
}
sf::Int16 Plateau::getTailleY()
{
	return 10;
}

void Plateau::deplacerVaisseau(Position ancienne, Position nouvelle)
{
	if (ancienne.x == xVaisseau && ancienne.y == yVaisseau && nouvelle.x < getTailleX() && nouvelle
			.y < getTailleY())
	{
		xVaisseau = nouvelle.x;
		yVaisseau = nouvelle.y;
	}
}
