/*
 * AffichagePlateau.cpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#include "AffichagePlateau.hpp"

#include <client/Jeu.hpp>

#include <client/utile/Utile.hpp>

#include <iostream>

AffichagePlateau::AffichagePlateau(Gui* gui, int id, int x, int y, int largeur,
	int hauteur) :
		Element(gui, id),
		ObservateurSouris(),
		cases(),
		details(nullptr),
		vuePlateau(sf::FloatRect(0, 0, 0, 0)),
		vueInterface(sf::FloatRect(0, 0, 0, 0))
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	vuePlateau.setViewport(sf::FloatRect(0, 0, 1, 0.7f));
	vueInterface.setViewport(sf::FloatRect(0, 0, 1, 1));

	details = AffichageDetailsPtr(
			new AffichageDetails(
					gui,
					0,
					2,
					lireGui()->lireScene()->lireJeu().lireAffichage().getSize()
							.y - 102,
					250, 100));

	vuePlateau.setSize(2000, 1000);
	vuePlateau.move(200, -50);
	vueInterface.setSize(
			lireGui()->lireScene()->lireJeu().lireAffichage().getSize().x,
			lireGui()->lireScene()->lireJeu().lireAffichage().getSize().y);

	int taille = 25;
	int k = 0;

	for (int i = 0;
			i < lireGui()->lireScene()->lireJeu().lirePlateau().getTailleX();
			i++)
		for (int j = 0;
				j < lireGui()->lireScene()->lireJeu().lirePlateau().getTailleY();
				j++)
		{
			int x = i * taille;
			int y = j * taille + j * 5;

			if (i % 2 == 1)
				y += taille * 3 / 5;

			AffichageCase* c = new AffichageCase(gui, k++, x, y, taille,
													Position(i, j),
													&vuePlateau);

			cases.push_back(AffichageCase::Ptr(c));
		}
}

AffichagePlateau::~AffichagePlateau()
{
	details.reset();
}

void AffichagePlateau::actualiser(float delta)
{
	if (details->estSelectionne())
	{
		// Un vaisseau est selectionne, actualiser les cases qu'il peut atteindre
	}

	// On actualise l'affichage des détails
	details->actualiser(delta);

	// Pour toutes les cases
	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
	{
		//cases[i]->actualiser(delta);
	}
}

void AffichagePlateau::bougerPlateau(float x, float y)
{
	vuePlateau.move(x, y);
}

void AffichagePlateau::afficher(sf::RenderWindow& affichage)
{
	affichage.setView(vueInterface);

	details->afficher(affichage);

	affichage.setView(vuePlateau);

	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
	{
		cases[i]->afficher(affichage);
	}

	affichage.setView(affichage.getDefaultView());
}

bool AffichagePlateau::contient(sf::Vector2i)
{
	return false;
}

// Héritées d'ElementSouris
void AffichagePlateau::clicSouris()
{

}

void AffichagePlateau::pressionSouris(sf::Mouse::Button)
{
	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
	{
		//cases[i]->surPressionBoutonSouris(evenement);
	}
}
void AffichagePlateau::relachementSouris(sf::Mouse::Button)
{
	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
	{
		//cases[i]->surMouvementSouris(evenement);
	}
}
void AffichagePlateau::entreeSouris(sf::Vector2f)
{

}
void AffichagePlateau::sortieSouris(sf::Vector2f)
{

}
void AffichagePlateau::moletteSouris(int delta)
{
	if (delta <= 0 && vuePlateau.getSize().x < 2000)
		vuePlateau.zoom(1.1);
	else if (delta >= 0 && vuePlateau.getSize().x > 100)
		vuePlateau.zoom(0.9);
}

// Héritées d'ElementClavier
void AffichagePlateau::pressionTouche(sf::Keyboard::Key)
{

}
void AffichagePlateau::relachementTouche(sf::Keyboard::Key)
{

}
void AffichagePlateau::entreeTexte(sf::Uint32)
{

}
