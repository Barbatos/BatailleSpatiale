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

AffichagePlateau::AffichagePlateau(int nom, int x, int y, int largeur,
	int hauteur) :
		Element(nom, x, y, largeur, hauteur),
		ElementSouris(),
		cases(),
		details(nullptr),
		vuePlateau(sf::FloatRect(0, 0, 0, 0)),
		vueInterface(sf::FloatRect(0, 0, 0, 0))
{
	vuePlateau.setViewport(sf::FloatRect(0, 0, 1, 0.7f));
	vueInterface.setViewport(sf::FloatRect(0, 0, 1, 1));
}

AffichagePlateau::~AffichagePlateau()
{
	details.reset();
}

void AffichagePlateau::initialiser()
{
	details = AffichageDetailsPtr(
			new AffichageDetails(
					0, 2, parent->lireJeu().lireAffichage().getSize().y - 102,
					250, 100));

	details->changerParent(parent.get());

	vuePlateau.setSize(2000, 1000);
	vuePlateau.move(200, -50);
	vueInterface.setSize(parent->lireJeu().lireAffichage().getSize().x,
							parent->lireJeu().lireAffichage().getSize().y);

	details->initialiser();

	int taille = 25;
	int k = 0;

	for (int i = 0; i < parent->lireJeu().lirePlateau().getTailleX(); i++)
		for (int j = 0; j < parent->lireJeu().lirePlateau().getTailleY(); j++)
		{
			int x = i * taille;
			int y = j * taille + j * 5;

			if (i % 2 == 1)
				y += taille * 3 / 5;

			AffichageCase* c = new AffichageCase(k++, x, y, taille,
													Position(i, j),
													&vuePlateau);

			c->changerParent(parent.get());

			c->initialiser();

			cases.push_back(AffichageCasePtr(c));
		}
}

void AffichagePlateau::actualiser(float delta)
{
	if (details->estSelectionne())
	{
		// Un vaisseau est selectionne, actualiser les cases qu'il peut atteindre
	}

	// On actualise l'affichage des détails
	details->actualiser(delta);

	cout << "gettaillex:" << parent->lireJeu().lirePlateau().getTailleX() << endl;
	
	// Pour toutes les cases
	for (std::vector<AffichageCasePtr>::size_type i = 0; i < cases.size(); i++)
	{
		cases[i]->actualiser(delta);
	}
}

void AffichagePlateau::bougerPlateau(float x, float y)
{
	vuePlateau.move(x, y);
}

void AffichagePlateau::afficher(Affichage& affichage)
{
	affichage.setView(vueInterface);

	details->afficher(affichage);

	affichage.setView(vuePlateau);

	for (std::vector<AffichageCasePtr>::size_type i = 0; i < cases.size(); i++)
	{
		cases[i]->afficher(affichage);
	}

	affichage.setView(affichage.getDefaultView());
}

void AffichagePlateau::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	for (std::vector<AffichageCasePtr>::size_type i = 0; i < cases.size(); i++)
	{
		cases[i]->surMouvementSouris(evenement);
	}
}

void AffichagePlateau::surPressionBoutonSouris(
	sf::Event::MouseButtonEvent evenement)
{
	for (std::vector<AffichageCasePtr>::size_type i = 0; i < cases.size(); i++)
	{
		cases[i]->surPressionBoutonSouris(evenement);
	}
}

void AffichagePlateau::surRelachementBoutonSouris(sf::Event::MouseButtonEvent)
{
	// On ne fait rien
}

void AffichagePlateau::surMoletteSouris(sf::Event::MouseWheelEvent evenement)
{
	if (evenement.delta <= 0 && vuePlateau.getSize().x < 2000)
		vuePlateau.zoom(1.1);
	else if (evenement.delta >= 0 && vuePlateau.getSize().x > 100)
		vuePlateau.zoom(0.9);
}

void AffichagePlateau::surPressionToucheClavier(sf::Event::KeyEvent)
{

}

void AffichagePlateau::surRelachementToucheClavier(sf::Event::KeyEvent)
{

}

void AffichagePlateau::surTexteClavier(sf::Event::TextEvent)
{

}
