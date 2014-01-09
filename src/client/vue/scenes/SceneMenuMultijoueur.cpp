/*
 * SceneMenuMultijoueur.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */

#include "SceneMenuMultijoueur.hpp"

#include <client/Jeu.hpp>

SceneMenuMultijoueur::SceneMenuMultijoueur(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 3;

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Multijoueur, "Lancer partie", x, y, largeur, hauteur);
	new Bouton(&gui, Retour, "Retour", x, 2 * y, largeur, hauteur);
}

SceneMenuMultijoueur::~SceneMenuMultijoueur()
{
}

void SceneMenuMultijoueur::surMessage(int id)
{
	switch (id)
	{
		case Multijoueur:
			jeu.changer(Scene::SceneJeu);
			break;
		case Retour:
			jeu.changer(Scene::SceneMenuPrincipal);
			break;
		default:
			break;
	}
}
