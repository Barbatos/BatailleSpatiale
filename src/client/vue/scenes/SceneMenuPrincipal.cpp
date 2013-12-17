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
	new Image(&gui, 0, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	new Bouton(&gui, Quitter, "Quitter", 50, 50, 100, 20);
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
			jeu.changer(Scene::SceneMenuMultijoueur);
			break;
		case Serveur:
			jeu.changer(Scene::SceneLancerServeur);
			break;
		case Quitter:
			jeu.quitter();
			break;
		case Musique:
			if (musique->getStatus() == sf::Music::Playing)
				musique->pause();
			else
				musique->play();
			break;
		case Options:
			jeu.changer(Scene::SceneOptionsMenu);
			break;
		default:
			break;
	}
}
