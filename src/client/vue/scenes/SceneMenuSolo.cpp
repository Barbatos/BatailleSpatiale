/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneMenuSolo.hpp"

#include <client/vue/gui/elements/ZoneTexte.hpp>
#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuSolo::SceneMenuSolo(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 3;

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Solo, "Lancer partie", x, y, largeur, hauteur);

	new Bouton(&gui, Retour, "Retour", x, 2 * y, largeur, hauteur);
}

SceneMenuSolo::~SceneMenuSolo()
{
}

void SceneMenuSolo::surMessage(int id)
{
	switch (id)
	{
		case Solo:
			jeu.lancerServeurGUI(1337);
			jeu.lireReseau()->ConnexionServeur("127.0.0.1", 1337);
			break;
		case Retour:
			jeu.changer(Scene::SceneMenuPrincipal);
			break;
		default:
			break;
	}
}
