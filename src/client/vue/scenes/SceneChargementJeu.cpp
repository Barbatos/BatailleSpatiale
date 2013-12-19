/*
 * SceneChargementReseau.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "SceneChargementJeu.hpp"

#include <client/vue/gui/elements/ChargementJeu.hpp>

SceneChargementJeu::SceneChargementJeu(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new ChargementJeu(&gui, 0);
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
		default:
			break;
	}
}
