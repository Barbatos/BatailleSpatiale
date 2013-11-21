/*
 * ZoneTexte.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Soinou
 */

#include "ZoneTexte.hpp"

#include <sstream>

#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

ZoneTexte::ZoneTexte(int nom, int x, int y, int largeur, int hauteur) :
		Element(nom, x, y, largeur, hauteur),
		ElementSouris(),
		ElementClavier(),
		rectangle(),
		label(),
		survole(false),
		selectionne(false),
		texte()
{
	rectangle.setPosition(x, y);
	rectangle.setSize(sf::Vector2f(largeur, hauteur));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setFillColor(sf::Color(255, 255, 255, 0));

	label.setPosition(x, y);
	label.setColor(sf::Color(255, 255, 255));
}

ZoneTexte::~ZoneTexte()
{

}

void ZoneTexte::initialiser()
{
	label.setFont(parent->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
}

void ZoneTexte::actualiser(__attribute__((unused)) float delta)
{
	if (selectionne)
		rectangle.setOutlineColor(sf::Color(255, 0, 0));
	else if (survole)
		rectangle.setOutlineColor(sf::Color(255, 255, 0));
	else
		rectangle.setOutlineColor(sf::Color(255, 255, 255));
}

void ZoneTexte::afficher(__attribute__((unused))     Affichage& affichage)
{
	affichage.draw(rectangle);
	affichage.draw(label);
}

void ZoneTexte::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	if (rectangle.getGlobalBounds().contains(evenement.x, evenement.y))
	{
		survole = true;
	}
	else
	{
		survole = false;
	}
}

void ZoneTexte::surPressionBoutonSouris(
	__attribute__((unused))     sf::Event::MouseButtonEvent evenement)
{

}

void ZoneTexte::surRelachementBoutonSouris(
	sf::Event::MouseButtonEvent evenement)
{
	if (survole && evenement.button == sf::Mouse::Left)
	{
		selectionne = true;
	}
	else
	{
		selectionne = false;
	}
}

void ZoneTexte::surMoletteSouris(
	__attribute__((unused))     sf::Event::MouseWheelEvent evenement)
{

}

void ZoneTexte::surPressionToucheClavier(
	__attribute__((unused))     sf::Event::KeyEvent evenement)
{
}

void ZoneTexte::surRelachementToucheClavier(
	__attribute__((unused))     sf::Event::KeyEvent evenement)
{

}

void ZoneTexte::surTexteClavier(sf::Event::TextEvent evenement)
{

	if (selectionne)
	{
		if (evenement.unicode == 8)
		{
			texte = texte.substr(0, texte.size() - 1);

			label.setString(texte);
		}
		else
		{
			char c = (char) evenement.unicode;

			std::stringstream stream;

			stream
				<< texte
				<< c;

			texte = stream.str();

			label.setString(texte);
		}

	}
}
