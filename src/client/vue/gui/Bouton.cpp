/*
 * Bouton.cpp
 *
 *  Created on: 5 oct. 2013
 *      Author: Tendry
 */

#include "Bouton.hpp"

// Includes des classes pré-déclarées et/ou dont on a besoin
#include <client/utile/Utile.hpp>
#include <client/Jeu.hpp>

// Includes de la libstd
#include <iostream>

Bouton::Bouton(int nom, std::string texte, float x, float y, float largeur,
	float hauteur) :
		Element(nom, x, y, largeur, hauteur),
		ElementSouris(),
		label(texte, x, y),
		survole(false),
		appuye(false)
{
}

Bouton::~Bouton()
{

}

void Bouton::initialiser()
{
	normal = parent->lireJeu().lireRessources().lireImage(
			"Interface/Bouton/bouton.png");
	survol = parent->lireJeu().lireRessources().lireImage(
			"Interface/Bouton/bouton_dessus.png");
	appui = parent->lireJeu().lireRessources().lireImage(
			"Interface/Bouton/bouton_clic.png");

	Utile::redimensionnerImage(normal, zone.width, zone.height, true);
	normal.setPosition(zone.left, zone.top);
	Utile::redimensionnerImage(survol, zone.width, zone.height, true);
	survol.setPosition(zone.left, zone.top);
	Utile::redimensionnerImage(appui, zone.width, zone.height, true);
	appui.setPosition(zone.left, zone.top);

	zone = normal.getGlobalBounds();

	label.setFont(parent->lireJeu().lireRessources().lirePolice("grand9k.ttf"));

	label.setOrigin(-(zone.width - label.getGlobalBounds().width) / 2,
					-(zone.height - label.getGlobalBounds().height) / 2);
}

void Bouton::actualiser(__attribute__((unused)) float delta)
{

}

void Bouton::afficher(Affichage& affichage)
{
	if (appuye)
		affichage.draw(appui);
	else if (survole)
		affichage.draw(survol);
	else
		affichage.draw(normal);

	affichage.draw(label);
}

void Bouton::surMoletteSouris(
	__attribute__((unused))     sf::Event::MouseWheelEvent evenement)
{
	// Ne rien faire
}

void Bouton::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	if (!survole && zone.contains(evenement.x, evenement.y))
	{
		survole = true;
		parent->lireJeu().lireRessources().jouerSon("menuhit.wav");
		envoyerMessage(Scene::Entre);
	}
	else if (survole && !zone.contains(evenement.x, evenement.y))
	{
		survole = false;
		envoyerMessage(Scene::Sort);
	}
}

void Bouton::surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement)
{
	if (survole && evenement.button == sf::Mouse::Left)
		appuye = true;
}

void Bouton::surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement)
{
	if (survole && appuye && evenement.button == sf::Mouse::Left)
	{
		appuye = false;
		parent->lireJeu().lireRessources().jouerSon("menuclick.wav");
		envoyerMessage(Scene::Clic);
	}
	else if (!survole && appuye)
		appuye = false;
}
