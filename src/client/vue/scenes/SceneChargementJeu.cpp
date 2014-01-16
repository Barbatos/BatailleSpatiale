/*
 * SceneChargementReseau.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "SceneChargementJeu.hpp"

#include <client/vue/gui/elements/chargement/ChargementReseau.hpp>
#include <client/vue/gui/elements/generiques/Bouton.hpp>

SceneChargementJeu::SceneChargementJeu(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	int largeur = jeu.lireAffichage().getSize().x / 2;
	int hauteur = jeu.lireAffichage().getSize().y / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;
	int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

	new ChargementReseau(&gui, 0, x, y, largeur, hauteur);

	largeur = 300 / 1.5;
	hauteur = 86 / 1.5;

	x = (jeu.lireAffichage().getSize().x - largeur) / 2;
	y = jeu.lireAffichage().getSize().y - hauteur - 50;

	new Bouton(&gui, 1, "Retour", x, y, largeur, hauteur);
}

SceneChargementJeu::~SceneChargementJeu()
{
}

void SceneChargementJeu::surMessage(int id)
{
	switch (id)
	{
		case 0:
			lireJeu().changer(Scene::SceneJeu);
			break;
		case 1:
			lireJeu().changer(Scene::SceneMenuSolo);
			break;
		default:
			break;
	}
}
