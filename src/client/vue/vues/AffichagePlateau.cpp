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
		vuePlateau(sf::FloatRect(0, 0, 0, 0))
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	enregistrerSouris(ObservateurSouris::Ptr(this));

	vuePlateau.setViewport(sf::FloatRect(0, 0, 1, 0.7f));

	int taille = 25;
	int k = 0;

	int xc = 0;
	int yc = 0;

	for (int i = 0;
			i < lireGui()->lireScene()->lireJeu().lirePlateau().getTailleX();
			i++)
		for (int j = 0;
				j < lireGui()->lireScene()->lireJeu().lirePlateau().getTailleY();
				j++)
		{
			xc = i * taille;
			yc = j * taille + j * 5;

			if (i % 2 == 1)
				yc += taille * 3 / 5;

			AffichageCase* c = new AffichageCase(gui, k++, xc, yc, taille,
													Position(i, j),
													&vuePlateau);

			cases.push_back(AffichageCase::Ptr(c));
		}

	if (xc > yc)
		taille = yc;
	else
		taille = xc;

	vuePlateau.setSize(taille * 0.9, taille * 0.9);
	vuePlateau.move(taille / 2, taille / 2);
}

AffichagePlateau::~AffichagePlateau()
{
	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
		cases[i].release();

	cases.clear();
}

void AffichagePlateau::actualiser(float)
{
}

void AffichagePlateau::bougerPlateau(float x, float y)
{
	vuePlateau.move(x, y);
}

void AffichagePlateau::afficher(sf::RenderWindow&)
{

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

}
void AffichagePlateau::relachementSouris(sf::Mouse::Button)
{

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
