/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu) :
		Scene(jeu),
		plateau(Plateau, 640, 0, 640, 376)
{
	float largeur = 300 / 2;
	float hauteur = 86 / 2;

	float x = (jeu.lireAffichage().getSize().x - largeur);
	float y = (jeu.lireAffichage().getSize().y - hauteur);

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.jpg")));

	Bouton* btnpause = new Bouton(Pause, "Pause", x, y, largeur, hauteur);

	ajouter(btnpause);
	ajouter(&plateau);

	enregistrerSouris(btnpause);
	enregistrerSouris(&plateau);
}

SceneJeu::~SceneJeu()
{

}

void SceneJeu::surMessage(int nom, Scene::Message message)
{
	switch (message)
	{
		case Clic:
			switch (nom)
			{
				case Pause:
					jeu.changer(Scene::SceneJeuMenu);
					break;
				case Plateau:
					break;
				default:
					break;
			}
			break;
		case Entre:
			break;
		case Sort:
			break;
		default:
			break;
	}
}
