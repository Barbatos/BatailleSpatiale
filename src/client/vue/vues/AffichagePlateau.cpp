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
		details(nullptr),
		tailleCase(0),
		selection(-1, -1),
		survol(-1, -1),
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
	vueInterface.setSize(parent->lireJeu().lireAffichage().getSize().x,
							parent->lireJeu().lireAffichage().getSize().y);

	details->initialiser();

	tailleCase = 25;

	for (int i = 0; i < parent->lireJeu().lirePlateau().getTailleX(); i++)
		for (int j = 0; j < parent->lireJeu().lirePlateau().getTailleY(); j++)
		{
			Case c;

			c.x = (i * 2 + j) * tailleCase * 3 / 5;
			c.y = j * tailleCase;
			c.position = Position(i, j);
			c.image = sf::Sprite();
			c.fond = sf::CircleShape(tailleCase / 2, 6);
			c.fond.setPosition(c.x, c.y);
			c.fond.setFillColor(sf::Color(0, 0, 0, 0));
			c.fond.setOutlineColor(sf::Color(255, 255, 255));
			c.fond.setOutlineThickness(2);
			cases.push_back(c);
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

	// Pour toutes les cases
	for (std::vector<Case>::size_type i = 0; i < cases.size(); i++)
	{
		// Si la case contient un vaisseau
		if (parent->lireJeu().lirePlateau().possedeVaisseau(cases[i].position))
		{
			// On met l'image du vaisseau correspondant
			cases[i].image = parent->lireJeu().lireRessources().lireImage(
					"Vaisseaux/sprite_bombardier_1.png");
			cases[i].image.setTextureRect(sf::IntRect(2400, 0, 480, 480));
			cases[i].image.setPosition(cases[i].x, cases[i].y);
			Utile::redimensionnerImage(cases[i].image, tailleCase, tailleCase,
										false);
		}
		// Si elle contient un batiment
		else if (parent->lireJeu().lirePlateau().possedeBatiment(
				cases[i].position))
		{
			// On met l'image du bâtiment correspondant
		}
		// Si elle contient un évènement
		else if (parent->lireJeu().lirePlateau().possedeEvenement(
				cases[i].position))
		{
			// On met l'image de l'évènement correspondantz
		}
		// Sinon, case vide
		else
		{
			// On réinitialise l'image
			cases[i].image = sf::Sprite();
		}

		// Selon que la case soit selectionnée, survolée, ou rien du tout, on change la couleur de la bordure
		if (selection == cases[i].position)
			cases[i].fond.setOutlineColor(sf::Color(255, 255, 0));
		else if (survol == cases[i].position)
			cases[i].fond.setOutlineColor(sf::Color(255, 0, 0));
		else
			cases[i].fond.setOutlineColor(sf::Color(255, 255, 255));
	}
}

void AffichagePlateau::afficher(Affichage& affichage)
{
	affichage.setView(vueInterface);

	details->afficher(affichage);

	affichage.setView(vuePlateau);

	for (std::vector<Case>::size_type i = 0; i < cases.size(); i++)
	{
		affichage.draw(cases[i].fond);
		affichage.draw(cases[i].image);
	}

	affichage.setView(affichage.getDefaultView());
}

Position AffichagePlateau::positionCellule(sf::Vector2f souris)
{
	Position position(
			(((int) souris.x) / (tailleCase * 3 / 5) - ((int) souris.y) / tailleCase) / 2,
			((int) souris.y) / tailleCase);

	if ((position.x >= 0 && position.x < parent->lireJeu().lirePlateau()
			.getTailleX()) && (position.y >= 0 && position.y < parent->lireJeu()
			.lirePlateau().getTailleY()))
		return position;
	else
		return Position(-1, -1);
}

void AffichagePlateau::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	survol = positionCellule(
			parent->lireJeu().lireAffichage().mapPixelToCoords(
					sf::Vector2i(evenement.x, evenement.y), vuePlateau));
}

void AffichagePlateau::surPressionBoutonSouris(
	sf::Event::MouseButtonEvent evenement)
{
	Position cellule = positionCellule(
			parent->lireJeu().lireAffichage().mapPixelToCoords(
					sf::Vector2i(evenement.x, evenement.y), vuePlateau));

	std::cout
		<< "X : "
		<< cellule.x
		<< "Y : "
		<< cellule.y
		<< std::endl;

	// Si la case selectionne n'est pas vide
	if (cellule.x != -1 && cellule.y != -1)
	{
		// Si la précédente case selectionnée n'est pas vide
		if (selection.x != -1 && selection.y != -1)
		{
			// Si c'est un batiment
			if (parent->lireJeu().lirePlateau().possedeBatiment(selection))
			{
				// On effectue les actions liées aux batiments
			}
			// Si c'est un vaisseau
			else if (parent->lireJeu().lirePlateau().possedeVaisseau(selection))
			{
				// Si la destination possède un vaisseau
				if (parent->lireJeu().lirePlateau().possedeVaisseau(cellule))
				{
					// Si c'est un ennemi, on l'attaque, sinon on ne fait rien
				}
				// Si la destination possède un batiment
				else if (parent->lireJeu().lirePlateau().possedeBatiment(
						cellule))
				{
					// Ennemi : attaque, Allié : rien
				}
				// Si la destination possède un évènement
				else if (parent->lireJeu().lirePlateau().possedeEvenement(
						cellule))
				{
					// On ne fait rien
				}
				// Sinon, case vide
				else
				{
					parent->lireJeu().lirePlateau().deplacerVaisseau(
							selection, cellule);
				}
				// On effectue les actions liées aux vaisseaux
			}
			// Si c'est un évènement
			else if (parent->lireJeu().lirePlateau().possedeEvenement(
					selection))
			{
				// On effectue les actions liées aux evenements
			}
		}
		// Aucune case n'a encore été selectionnée
		else
		{

		}
	}

	// Puis on sélectionne la nouvelle case
	selection = cellule;
	details->selectionner(selection);
}

void AffichagePlateau::surRelachementBoutonSouris(sf::Event::MouseButtonEvent)
{
	// On ne fait rien
}

void AffichagePlateau::surMoletteSouris(sf::Event::MouseWheelEvent evenement)
{
	if (evenement.delta <= 0)
		vuePlateau.zoom(1.5 * -(evenement.delta));
	else
		vuePlateau.zoom(0.5 * evenement.delta);
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
