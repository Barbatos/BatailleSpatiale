/*
 * Splash.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "Splash.hpp"

#include <sstream>

#include <iostream>

#include <client/utile/Utile.hpp>

Splash Splash::instance;

Splash::Splash() :
		fenetre(),
		texture(),
		sprite(),
		police(),
		label(),
		texte("Bataille Spatiale"),
		valeur(0),
		maxi(100),
		fin(false)
{
	police.loadFromFile("ressources/polices/grand9k.ttf");
	texture.loadFromFile("ressources/images/Interface/splash_screen.png");
	texture.setSmooth(true);

	sprite.setTexture(texture);
	Utile::redimensionnerImage(sprite, 576, 324, true);
	sprite.setPosition((576 - sprite.getGlobalBounds().width) / 2,
						(324 - sprite.getGlobalBounds().height) / 2);

	label.setFont(police);
	label.setCharacterSize(14);
	label.setPosition(0, 324 - label.getCharacterSize());

	fenetre.create(sf::VideoMode(576, 324), "Splash", sf::Style::None);
	fenetre.setVerticalSyncEnabled(true);
}

Splash::~Splash()
{
}

void Splash::lancer()
{
	while (!fin)
	{
		fenetre.clear();

		actualiser();

		dessiner();

		fenetre.display();
	}

	fenetre.close();
}

void Splash::fermer()
{
	this->fin = true;
}

void Splash::actualiser()
{
	std::stringstream stream;

	stream
		<< texte
		<< " "
		<< (valeur * 100 / maxi)
		<< "%";

	label.setString(stream.str());
}

void Splash::dessiner()
{
	fenetre.draw(sprite);
	fenetre.draw(label);
}

std::string Splash::lireTexte()
{
	return texte;
}

int Splash::lireValeur()
{
	return valeur;
}

int Splash::lireMaxi()
{
	return maxi;
}

void Splash::changerTexte(std::string texte)
{
	this->texte = texte;
}

void Splash::changerValeur(int valeur)
{
	this->valeur = valeur;
}

void Splash::changerMaxi(int maxi)
{
	this->maxi = maxi;
}

Splash& Splash::lireInstance()
{
	return instance;
}
