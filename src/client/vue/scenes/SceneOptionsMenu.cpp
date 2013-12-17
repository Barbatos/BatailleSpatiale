/*
 * SceneOptionsMenu.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */
#include "SceneOptionsMenu.hpp"

#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneOptionsMenu::SceneOptionsMenu(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Retour, "Retour", x, y, largeur, hauteur);
}

SceneOptionsMenu::~SceneOptionsMenu()
{
}

void SceneOptionsMenu::surMessage(int id)
{
	switch (id)
	{
		case Retour:
			jeu.changer(Scene::SceneMenuPrincipal);
			break;
		default:
			break;
	}
}
