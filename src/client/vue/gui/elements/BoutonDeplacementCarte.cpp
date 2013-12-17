/*
 * BoutonDeplacementCarte.cpp
 *
 *  Created on: 5 d�c. 2013
 *      Author: Thornydre
 */

#include "BoutonDeplacementCarte.hpp"

// Includes des classes pré-déclarées et/ou dont on a besoin
#include <client/utile/Utile.hpp>
#include <client/Jeu.hpp>

// Includes de la libstd
#include <iostream>

BoutonDeplacementCarte::BoutonDeplacementCarte(Gui* gui, int id, float x,
	float y, float largeur, float hauteur) :
		Element(gui, id),
		ObservateurSouris(),
		normal(),
		survol()
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	normal.setPosition(x, y);
	normal.setSize(sf::Vector2f(largeur, hauteur));
	normal.setFillColor(sf::Color(50, 50, 50, 150));

	survol.setPosition(x, y);
	survol.setSize(sf::Vector2f(largeur, hauteur));
	survol.setFillColor(sf::Color(50, 50, 50, 200));
}

BoutonDeplacementCarte::~BoutonDeplacementCarte()
{

}

void BoutonDeplacementCarte::actualiser(float)
{
	if (lireSurvol())
		envoyerMessage();
}

void BoutonDeplacementCarte::afficher(sf::RenderWindow& affichage)
{
	if (lireSurvol())
		affichage.draw(survol);
	else
		affichage.draw(normal);
}

bool BoutonDeplacementCarte::contient(sf::Vector2i position)
{
	return normal.getGlobalBounds().contains(position.x, position.y);
}

void BoutonDeplacementCarte::clicSouris()
{

}
void BoutonDeplacementCarte::pressionSouris(sf::Mouse::Button)
{

}

void BoutonDeplacementCarte::relachementSouris(sf::Mouse::Button)
{

}

void BoutonDeplacementCarte::entreeSouris(sf::Vector2f)
{
	lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuhit.wav");
	envoyerMessage();
}

void BoutonDeplacementCarte::sortieSouris(sf::Vector2f)
{

}

void BoutonDeplacementCarte::moletteSouris(int)
{

}
