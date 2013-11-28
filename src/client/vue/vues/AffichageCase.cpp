/*
 * AffichageCase.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#include "AffichageCase.hpp"

#include <client/utile/Utile.hpp>
#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

AffichageCase::AffichageCase(int nom, float x, float y, float taille,
	Position position, sf::View* vuePlateau) :
		Element(nom, x, y, taille, taille),
		ElementSouris(),
		image(),
		fond(),
		position(position),
		survole(false),
		selectionne(false)
{
	fond = sf::CircleShape(taille / 2, 6);
	fond.setPosition(x + taille / 2, y + taille / 2);
	fond.setOrigin(taille / 2, taille / 2);
	fond.setFillColor(sf::Color(0, 0, 0, 0));
	fond.setOutlineColor(sf::Color(255, 255, 255));
	fond.setOutlineThickness(2);
	fond.rotate(30);

	this->vuePlateau = VuePtr(vuePlateau);
}

AffichageCase::~AffichageCase()
{
	// TODO Auto-generated destructor stub
}

void AffichageCase::initialiser()
{
}

void AffichageCase::actualiser(float)
{
	// Si la case contient un vaisseau
	if (parent->lireJeu().lirePlateau().possedeVaisseau(position))
	{
		// On met l'image du vaisseau correspondant
		image = parent->lireJeu().lireRessources().lireImage(
				"Vaisseaux/sprite_bombardier_1.png");
		image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
		image.setPosition(zone.left, zone.top);
		Utile::redimensionnerImage(image, zone.width, zone.width, false);
	}
	// Si elle contient un batiment
	else if (parent->lireJeu().lirePlateau().possedeBatiment(position))
	{
		// On met l'image du bâtiment correspondant
	}
	// Si elle contient un évènement
	else if (parent->lireJeu().lirePlateau().possedeEvenement(position))
	{
		// On met l'image de l'évènement correspondantz
	}
	// Sinon, case vide
	else
	{
		// On réinitialise l'image
		image = sf::Sprite();
	}

	// Selon que la case soit selectionnée, survolée, ou rien du tout, on change la couleur de la bordure
	if (selectionne)
		fond.setOutlineColor(sf::Color(255, 255, 0));
	else if (survole)
		fond.setOutlineColor(sf::Color(255, 0, 0));
	else
		fond.setOutlineColor(sf::Color(255, 255, 255));
}

void AffichageCase::afficher(Affichage& affichage)
{
	affichage.draw(fond);
	affichage.draw(image);
}

bool AffichageCase::contient(sf::Vector2f point)
{
	return point.x >= fond.getPosition().x - fond.getRadius() * 0.9 && point.x <= fond
			.getPosition().x + fond.getRadius() * 0.9 && point.y >= fond
			.getPosition().y - fond.getRadius() * 0.9 && point.y <= fond
			.getPosition().y + fond.getRadius() * 0.9;
}

void AffichageCase::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	if (contient(
			parent->lireJeu().lireAffichage().mapPixelToCoords(
					sf::Vector2i(evenement.x, evenement.y),
					*(vuePlateau.get()))))
		survole = true;
	else
		survole = false;
}

void AffichageCase::surPressionBoutonSouris(
	sf::Event::MouseButtonEvent evenement)
{
	if (survole && evenement.button == sf::Mouse::Left)
		selectionne = true;
	else
		selectionne = false;
}

void AffichageCase::surRelachementBoutonSouris(sf::Event::MouseButtonEvent)
{

}

void AffichageCase::surMoletteSouris(sf::Event::MouseWheelEvent)
{

}

