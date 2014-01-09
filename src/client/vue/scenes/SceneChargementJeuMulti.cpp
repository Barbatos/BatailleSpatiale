/*
 * SceneChargementJeuMulti.cpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Soinou
 */

#include "SceneChargementJeuMulti.hpp"

SceneChargementJeuMulti::SceneChargementJeuMulti(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));
}

SceneChargementJeuMulti::~SceneChargementJeuMulti()
{

}

void SceneChargementJeuMulti::surMessage(int id)
{
	switch (id)
	{
		default:
			break;
	}
}
