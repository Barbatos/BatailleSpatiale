/*
 * SceneChargementReseau.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#include "SceneChargementReseau.hpp"

#include <client/vue/gui/elements/ChargementReseau.hpp>

SceneChargementReseau::SceneChargementReseau(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new ChargementReseau(&gui, 0);
}

SceneChargementReseau::~SceneChargementReseau()
{
}

void SceneChargementReseau::surMessage(int id)
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
