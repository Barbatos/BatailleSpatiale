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

AffichageCase::AffichageCase(Gui* gui, int id, float x, float y, float taille,
	Position position, sf::View* vuePlateau) :
		Element(gui, id),
		image(),
		fond(),
		position(position),
		selectionne(false)
{
	ecrirePosition(x, y);
	ecrireTaille(taille, taille);
	ecrireVue(vuePlateau);

	enregistrerSouris(ObservateurSouris::Ptr(this));

	fond = sf::CircleShape(taille / 2, 6);
	fond.setPosition(x + taille / 2, y + taille / 2);
	fond.setOrigin(taille / 2, taille / 2);
	fond.setFillColor(sf::Color(0, 0, 0, 0));
	fond.setOutlineColor(sf::Color(255, 255, 255));
	fond.setOutlineThickness(2);
	fond.rotate(30);
}

AffichageCase::~AffichageCase()
{
}

void AffichageCase::actualiser(float)
{
	// Si la case contient un vaisseau
	if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeVaisseau(
			position))
	{
		// On met l'image du vaisseau correspondant
		image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(
				"Vaisseaux/sprite_bombardier_1.png");
		image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
		image.setPosition(lirePosition().x, lirePosition().y);
		Utile::redimensionnerImage(image, lireTaille().x, lireTaille().y,
									false);
	}
	// Si elle contient un batiment
	else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeBatiment(
			position))
	{
		// On met l'image du bâtiment correspondant
	}
	// Si elle contient un évènement
	else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeEvenement(
			position))
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
	else if (lireSurvol())
		fond.setOutlineColor(sf::Color(255, 0, 0));
	else
		fond.setOutlineColor(sf::Color(255, 255, 255));
}

void AffichageCase::afficher(sf::RenderWindow& affichage)
{
	affichage.draw(fond);
	affichage.draw(image);
}

bool AffichageCase::contient(sf::Vector2i position)
{
	return position.x >= fond.getPosition().x - fond.getRadius() * 0.9 && position
			.x <= fond.getPosition().x + fond.getRadius() * 0.9 && position.y >= fond
			.getPosition().y - fond.getRadius() * 0.9 && position.y <= fond
			.getPosition().y + fond.getRadius() * 0.9;
}

void AffichageCase::ecrirePositionPlateau(Position position)
{
	this->position = position;
}

Position AffichageCase::lirePositionPlateau()
{
	return position;
}

void AffichageCase::clicSouris()
{
	selectionne = true;
}

void AffichageCase::pressionSouris(sf::Mouse::Button)
{
	if (!lireSurvol())
		selectionne = false;
}

void AffichageCase::relachementSouris(sf::Mouse::Button)
{

}

void AffichageCase::entreeSouris(sf::Vector2f)
{

}

void AffichageCase::sortieSouris(sf::Vector2f)
{

}

void AffichageCase::moletteSouris(int)
{

}

