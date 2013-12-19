/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeuOptions.hpp"

#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneJeuOptions::SceneJeuOptions(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 2;

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Musique, "Musique", x, y, largeur, hauteur);
	new Bouton(&gui, Retour, "Retour", x, y, largeur, hauteur);

	musique = jeu.lireRessources().lireMusique("Clearness.ogg");
}

SceneJeuOptions::~SceneJeuOptions()
{
}

void SceneJeuOptions::surMessage(int id)
{
	switch (id)
	{
		case Retour:
			jeu.changer(Scene::SceneJeuMenu);
			break;
		case Musique:
			if (musique->getStatus() == sf::Music::Playing)
							musique->pause();
						else
							musique->play();
		break;
		default:
			break;
	}
}
