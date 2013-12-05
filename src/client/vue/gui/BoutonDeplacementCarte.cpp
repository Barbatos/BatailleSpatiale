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

BoutonDeplacementCarte::BoutonDeplacementCarte(int nom, float x, float y, float largeur, float hauteur) :
		Element(nom, x, y, largeur, hauteur),
		ElementSouris(),
		survole(false),
		normal(),
		survol()
{
	normal.setPosition(x, y);
	normal.setSize(sf::Vector2f(largeur, hauteur));
	normal.setFillColor(sf::Color(50, 50, 50, 150));

	survol.setPosition(x, y);
	survol.setSize(sf::Vector2f(largeur, hauteur));
	survol.setFillColor(sf::Color(50, 50, 50, 200));

	zone = normal.getGlobalBounds();
}

BoutonDeplacementCarte::~BoutonDeplacementCarte()
{

}

void BoutonDeplacementCarte::initialiser()
{

}

void BoutonDeplacementCarte::actualiser(__attribute__((unused)) float delta)
{
	if(survole)
		envoyerMessage(Scene::Clic);
}

void BoutonDeplacementCarte::afficher(Affichage& affichage)
{
	if(survole)
		affichage.draw(survol);
	else
		affichage.draw(normal);
}

void BoutonDeplacementCarte::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	if (!survole && zone.contains(evenement.x, evenement.y))
	{
		survole = true;
		parent->lireJeu().lireRessources().jouerSon("menuhit.wav");
		envoyerMessage(Scene::Clic);
	}
	else if (survole && !zone.contains(evenement.x, evenement.y))
	{
		survole = false;
	}
}

void BoutonDeplacementCarte::surPressionBoutonSouris(__attribute__((unused))      sf::Event::MouseButtonEvent evenement)
{

}

void BoutonDeplacementCarte::surRelachementBoutonSouris(__attribute__((unused))      sf::Event::MouseButtonEvent evenement)
{

}

void BoutonDeplacementCarte::surMoletteSouris(__attribute__((unused))      sf::Event::MouseWheelEvent evenement)
{

}
