/*
 * AffichageCase.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#include "AffichageCase.hpp"

#include <client/Jeu.hpp>
#include <iostream>

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
	std::string fichier = "";

	// Si la case contient un vaisseau
	if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeVaisseau(
			position))
	{
		DetailVaisseau details = lireGui()->lireScene()->lireJeu().lirePlateau()
				.getVaisseau(position);

		switch (details.type)
		{
			case TypeVaisseau::Inexistant:
				break;
			case TypeVaisseau::Simple:
				break;
			case TypeVaisseau::Constructeur:
				fichier = "Vaisseaux/sprite_constructeur_1.png";
				break;
			case TypeVaisseau::Bombardier:
				fichier = "Vaisseaux/sprite_bombardier_1.png";
				break;
			case TypeVaisseau::Chasseur:
				fichier = "Vaisseaux/sprite_chasseur_1.png";
				break;
			case TypeVaisseau::Croiseur:
				fichier = "Vaisseaux/sprite_croiseur_1.png";
				break;
			case TypeVaisseau::Destructeur:
				fichier = "Vaisseaux/sprite_destoyer_1.png";
				break;
			case TypeVaisseau::ChasseurLourd:
				break;
			case TypeVaisseau::Traqueur:
				break;
			case TypeVaisseau::Leger:
				break;
			default:
				break;
		}
	}
	// Si elle contient un batiment
	else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeBatiment(
			position))
	{
		DetailBatiment details = lireGui()->lireScene()->lireJeu().lirePlateau()
				.getBatiment(position);

		switch (details.type)
		{
			case TypeBatiment::Base:
				break;
			default:
				break;
		}
	}
	// Si elle contient un évènement
	else if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeEvenement(
			position))
	{
		DetailEvenement details = lireGui()->lireScene()->lireJeu().lirePlateau()
				.getEvenement(position);

		switch (details.type)
		{
			case TypeEvenement::ChampMeteor:
				break;
			case TypeEvenement::Epave:
				break;
			case TypeEvenement::InfluenceTrouNoir:
				break;
			case TypeEvenement::NuageGaz:
				break;
			case TypeEvenement::StationSpatialeAbandonnee:
				break;
			default:
				break;
		}
	}

	if (fichier == "")
		image = sf::Sprite();
	else
	{
		// On met l'image du vaisseau correspondant
		image = lireGui()->lireScene()->lireJeu().lireRessources().lireImage(
				fichier);
		image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
		image.setPosition(lirePosition().x, lirePosition().y);
		Utile::redimensionnerImage(image, lireTaille().x, lireTaille().y,
									false);
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

Position AffichageCase::lirePositionPlateau()
{
	return position;
}

bool AffichageCase::lireSelectionne()
{
	return selectionne;
}

void AffichageCase::ecrirePositionPlateau(Position position)
{
	this->position = position;
}

void AffichageCase::clicSouris()
{
	selectionne = true;
}

void AffichageCase::pressionSouris(sf::Mouse::Button)
{

}

void AffichageCase::relachementSouris(sf::Mouse::Button)
{
	if (!lireSurvol() && selectionne)
	{
		selectionne = false;
	}
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

