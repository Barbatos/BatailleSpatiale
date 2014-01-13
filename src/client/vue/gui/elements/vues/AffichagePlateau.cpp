/*
 * AffichagePlateau.cpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#include "AffichagePlateau.hpp"

#include <client/Jeu.hpp>

AffichagePlateau::AffichagePlateau(Gui* gui, int id, int x, int y, int largeur,
	int hauteur, AffichageDetails::Ptr details) :
		Element(gui, id),
		ObservateurSouris(),
		details(details),
		cases(),
		vuePlateau(sf::FloatRect(0, 0, 0, 0)),
		charge(false)

{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);
	ecrireVue(&vuePlateau);

	enregistrerSouris(ObservateurSouris::Ptr(this));

	vuePlateau.setViewport(sf::FloatRect(0, 0, 1, 0.7f));

	int taille = 25;

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

			AffichageCase* c = new AffichageCase(lireGui(), SceneJeu::Case, xc,
													yc, taille, Position(i, j),
													&vuePlateau);

			cases.push_back(AffichageCase::Ptr(c));
		}

	if (xc > yc)
		taille = yc;
	else
		taille = xc;

	vuePlateau.setSize(largeur, hauteur);
	vuePlateau.move(taille / 2, taille / 2);
}

AffichagePlateau::~AffichagePlateau()
{
	for (std::vector<AffichageCase::Ptr>::size_type i = 0; i < cases.size();
			i++)
		cases[i].reset();

	cases.clear();
}

void AffichagePlateau::actualiser(float)
{
	bool selection = false;
	Position position;

	// Pour toutes les cases, et tant que rien n'a été selectionné
	for (std::vector<AffichageCase::Ptr>::size_type i = 0;
			!selection && i < cases.size(); i++)
	{
		// Si la case est selectionnée
		if (cases[i]->lireSelectionne())
		{
			// On sauvegarde la position actuellement selectionnée
			position = details->lirePosition();
			// On selectionne la nouvelle
			details->selectionner(cases[i]->lirePositionPlateau());
			// On dit que quelque chose a été selectionné
			selection = true;
		}
	}

	// Si rien n'a été selectionné
	if (!selection)
		// Ne rien selectionner
		details->selectionner();
	// Sinon
	else
	{
		// Si une case était précédemment selectionnée
		if (position.x != -1 && position.y != -1)
		{
			// On récupère la nouvelle position
			// Position nouvelle = details->lirePosition();

			// Si la précédente case selectionnée contenait un vaisseau
			if (lireGui()->lireScene()->lireJeu().lirePlateau().possedeVaisseau(
					position))
			{
				// On déplace ce vaisseau
			}
			// Sinon, si c'était un bâtiment
			else if (lireGui()->lireScene()->lireJeu().lirePlateau()
					.possedeBatiment(position))
			{
				// Faire quelque chose
			}
		}
	}
}

void AffichagePlateau::bougerPlateau(float x, float y)
{
	vuePlateau.move(x, y);
}

void AffichagePlateau::appuiCase()
{

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
	/* Ne rien faire ici */
}

void AffichagePlateau::pressionSouris(sf::Mouse::Button)
{
}

void AffichagePlateau::relachementSouris(sf::Mouse::Button)
{

}
void AffichagePlateau::entreeSouris(sf::Vector2f)
{
	/* Ne rien faire ici */
}
void AffichagePlateau::sortieSouris(sf::Vector2f)
{
	/* Ne rien faire ici */
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
	/* Ne rien faire ici */
}
void AffichagePlateau::relachementTouche(sf::Keyboard::Key)
{

}
void AffichagePlateau::entreeTexte(sf::Uint32)
{
	/* Ne rien faire ici */
}
