/*
 * SceneMenuMultijoueur.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */

#include "SceneMenuMultijoueur.hpp"

#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuMultijoueur::SceneMenuMultijoueur(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.png")));

	Bouton* btnmultijoueur = new Bouton(Multijoueur, "Lancer partie", x, y, largeur, hauteur);

	ajouter(btnmultijoueur);

	enregistrerSouris(btnmultijoueur);
}

SceneMenuMultijoueur::~SceneMenuMultijoueur()
{
}

void SceneMenuMultijoueur::surMessage(int nom, Scene::Message message)
{
	switch (message)
	{
		case Clic:
			switch (nom)
			{
				case Multijoueur:
					jeu.changer(Scene::SceneJeu);
					break;
				default:
					break;
			}
			break;
		case Entre:
			break;
		case Sort:
			break;
	}
}


