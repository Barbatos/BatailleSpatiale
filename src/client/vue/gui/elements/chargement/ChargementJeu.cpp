/*
 * ChargementJeu.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "ChargementJeu.hpp"

#include <client/Jeu.hpp>

ChargementJeu::ChargementJeu(Gui* gui, int id, int x, int y, int largeur,
	int hauteur) :
		Element(gui, id),
		texte(),
		image(gui, -1, x, y, largeur, hauteur - texte.getCharacterSize() - 5,
				true, "Interface/chargement.png")
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	texte.setString("Chargement du reseau en cours ...");
	texte.setFont(
			gui->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
	texte.setPosition(x + (largeur - texte.getGlobalBounds().width) / 2,
						y + (hauteur - texte.getCharacterSize()));
}

ChargementJeu::~ChargementJeu()
{
}

void ChargementJeu::actualiser(float)
{
	if (lireGui()->lireScene()->lireJeu().lireReseau()->getActif() && lireGui()
			->lireScene()->lireJeu().lirePlateau().getTailleX() != 0)
		envoyerMessage();
}

void ChargementJeu::afficher(sf::RenderWindow& fenetre)
{
	fenetre.draw(texte);
}

bool ChargementJeu::contient(sf::Vector2i)
{
	return false;
}
