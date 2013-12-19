/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "SceneMenuPrincipal.hpp"

#include <iostream>
#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Animation.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuPrincipal::SceneMenuPrincipal(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;
	int y = (jeu.lireAffichage().getSize().y - hauteur) / 6;

	new Image(&gui, 0, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Animation(&gui, -1, 50, 100, 200, 200, true,
					"Environnement/comete2.png");

	new Bouton(&gui, Solo, "Partie Solo", x, y, largeur, hauteur);

	new Bouton(&gui, Multi, "Partie Multi", x, 2 * y, largeur, hauteur);

	new Bouton(&gui, Serveur, "Lancer un serveur", x, 3 * y, largeur, hauteur);

	new Bouton(&gui, Options, "Options", x, 4 * y, largeur, hauteur);

	new Bouton(&gui, Quitter, "Quitter", x, 5 * y, largeur, hauteur);
}

SceneMenuPrincipal::~SceneMenuPrincipal()
{

}

void SceneMenuPrincipal::surMessage(int id)
{
	switch (id)
	{
		case Solo:
			jeu.changer(Scene::SceneMenuSolo);
			break;
		case Multi:
			jeu.changer(Scene::SceneMenuMulti);
			break;
		case Serveur:
			jeu.changer(Scene::SceneLancerServeur);
			break;
		case Quitter:
			jeu.quitter();
			break;
		case Options:
			jeu.changer(Scene::SceneOptionsMenu);
			break;
		default:
			break;
	}
}
