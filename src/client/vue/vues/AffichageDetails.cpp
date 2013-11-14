/*
 * AffichageDetails.cpp
 *
 *  Created on: 18 oct. 2013
 *      Author: Soinou
 */

#include "AffichageDetails.hpp"
#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

#include <sstream>
#include <iostream>

AffichageDetails::AffichageDetails(int nom, float x, float y, float largeur,
		float hauteur) :
		Element(nom, x, y, largeur, hauteur), fond(), label("", x + 5, y), position(
				-1, -1)
{

}

AffichageDetails::~AffichageDetails()
{

}

void AffichageDetails::initialiser()
{
	fond.setPosition(zone.left, zone.top);
	fond.setSize(sf::Vector2f(zone.width, zone.height));
	fond.setFillColor(sf::Color(50, 50, 50));
	fond.setOutlineColor(sf::Color(100, 100, 100));
	fond.setOutlineThickness(2);

	label.setFont(parent->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
}

void AffichageDetails::actualiser(__attribute__((unused)) float delta)
{
	std::stringstream stream;

	if (position.x != -1 && position.y != -1)
	{
		if (parent->lireJeu().lirePlateau().possedeVaisseau(position))
		{
			stream << "Vie : "
					<< parent->lireJeu().lirePlateau().getVaisseau(position).vie
					<< "/"
					<< parent->lireJeu().lirePlateau().getVaisseau(position).vieMax
					<< "\n";
		}
		else if (parent->lireJeu().lirePlateau().possedeBatiment(position))
		{
			stream << "Vie : "
					<< parent->lireJeu().lirePlateau().getBatiment(position).vie
					<< "/"
					<< parent->lireJeu().lirePlateau().getBatiment(position).vieMax
					<< "\n";
		}
		else if (parent->lireJeu().lirePlateau().possedeEvenement(position))
		{
		}
		else
		{
			stream << "Case vide" << "Position : " << position.x << " : "
					<< position.y;
		}
	}
	else
	{
		stream << "";
	}

	label.setString(stream.str());
}

void AffichageDetails::afficher(Affichage& affichage)
{
	affichage.draw(fond);
	affichage.draw(label);
}

void AffichageDetails::selectionner(int i, int j)
{
	position = Position(i, j);
}

void AffichageDetails::selectionner(Position position)
{
	this->position = position;
}

void AffichageDetails::selectionner()
{
	position = Position(-1, -1);
}

bool AffichageDetails::estSelectionne()
{
	return position.x != -1 && position.y != -1;
}

Position AffichageDetails::lirePosition()
{
	return position;
}
