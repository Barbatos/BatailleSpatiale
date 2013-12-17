/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu) :
		Scene(jeu),
		plateau(&gui, Plateau, 640, 0, 640, 376)
{
	float largeur = 300 / 2;
	float hauteur = 86 / 2;

	float x = (jeu.lireAffichage().getSize().x - largeur);
	float y = (jeu.lireAffichage().getSize().y - hauteur);

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Pause, "Pause", x, y, largeur, hauteur);
	new Bouton(&gui, Droite, ">", jeu.lireAffichage().getSize().x - 50,
				(jeu.lireAffichage().getSize().y - 50) / 2, 50, 50);
	new Bouton(&gui, Gauche, "<", 0, (jeu.lireAffichage().getSize().y - 50) / 2,
				50, 50);
	new Bouton(&gui, Haut, "^", (jeu.lireAffichage().getSize().x - 50) / 2, 0,
				50, 50);
	new Bouton(&gui, Bas, "V", (jeu.lireAffichage().getSize().x - 50) / 2,
				6 * (jeu.lireAffichage().getSize().y) / 7, 50, 50);
}

SceneJeu::~SceneJeu()
{

}

void SceneJeu::surMessage(int id)
{
	switch (id)
	{
		case Pause:
			jeu.changer(Scene::SceneJeuMenu);
			break;
		case Plateau:
			break;
		case Droite:
			plateau.bougerPlateau(10, 0);
			break;
		case Gauche:
			plateau.bougerPlateau(-10, 0);
			break;
		case Haut:
			plateau.bougerPlateau(0, -10);
			break;
		case Bas:
			plateau.bougerPlateau(0, 10);
			break;
		default:
			break;
	}
}
