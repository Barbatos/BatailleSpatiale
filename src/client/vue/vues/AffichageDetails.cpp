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

AffichageDetails::AffichageDetails(Gui* gui, int id, float x, float y,
	float largeur, float hauteur) :
		Element(gui, id),
		fond(),
		label("", x + 5, y),
		position(-1, -1)
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	fond.setPosition(lirePosition().x, lirePosition().y);
	fond.setSize(sf::Vector2f(lireTaille().x, lireTaille().y));
	fond.setFillColor(sf::Color(50, 50, 50));
	fond.setOutlineColor(sf::Color(100, 100, 100));
	fond.setOutlineThickness(2);

	label.setFont(
			lireGui()->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
}

AffichageDetails::~AffichageDetails()
{

}

void AffichageDetails::actualiser(float)
{
	std::stringstream stream;

	if (position.x != -1 && position.y != -1)
	{
		if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeVaisseau(
				position))
		{
			stream
				<< "Vie : "
				<< lireGui()->lireScene()->lireJeu().lirePlateau().getVaisseau(
						position).vie
				<< "/"
				<< lireGui()->lireScene()->lireJeu().lirePlateau().getVaisseau(
						position).vieMax
				<< "\n";
		}
		else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeBatiment(
				position))
		{
			stream
				<< "Vie : "
				<< lireGui()->lireScene()->lireJeu().lirePlateau().getBatiment(
						position).vie
				<< "/"
				<< lireGui()->lireScene()->lireJeu().lirePlateau().getBatiment(
						position).vieMax
				<< "\n";
		}
		else if (lireGui()->lireScene()->lireJeu().lirePlateau()
				.possedeEvenement(position))
		{
		}
		else
		{
			stream
				<< "Case vide"
				<< "Position : "
				<< position.x
				<< " : "
				<< position.y;
		}
	}
	else
	{
		stream
			<< "";
	}

	label.setString(stream.str());
}

void AffichageDetails::afficher(sf::RenderWindow& affichage)
{
	affichage.draw(fond);
	affichage.draw(label);
}

bool AffichageDetails::contient(sf::Vector2i)
{
	return false;
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
