/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/vues/BoutonDeplacementPlateau.hpp>

#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	details = AffichageDetails::Ptr(
			new AffichageDetails(&gui, Details, 0,
									0.7 * jeu.lireAffichage().getSize().y,
									jeu.lireAffichage().getSize().x / 3,
									0.3 * jeu.lireAffichage().getSize().y));

	plateau = AffichagePlateau::Ptr(
			new AffichagePlateau(&gui, Plateau, 30, 30, 580, 316,
									details));

	new BoutonDeplacementPlateau(&gui, Droite,
									jeu.lireAffichage().getSize().x - 30, 30,
									30,
									0.7 * jeu.lireAffichage().getSize().y - 60);
	new BoutonDeplacementPlateau(&gui, Gauche, 0, 30, 30,
									0.7 * jeu.lireAffichage().getSize().y - 60);
	new BoutonDeplacementPlateau(&gui, Haut, 30, 0,
									jeu.lireAffichage().getSize().x - 60, 30);
	new BoutonDeplacementPlateau(&gui, Bas, 30,
									0.7 * jeu.lireAffichage().getSize().y - 30,
									jeu.lireAffichage().getSize().x - 60, 30);
	new Bouton(&gui, Menu, "Menu", jeu.lireAffichage().getSize().x - 40,
				jeu.lireAffichage().getSize().y - 40, 40, 40);
}

SceneJeu::~SceneJeu()
{

}

void SceneJeu::surMessage(int id)
{
	switch (id)
	{
		case Menu:
			jeu.changer(Scene::SceneJeuMenu);
			break;
		case Plateau:
			break;
		case Droite:
			if (plateau->lireVue()->getCenter().x < jeu.lireAffichage().getSize()
					.x / 2)
				plateau->bougerPlateau(5, 0);
			break;
		case Gauche:
			if (-plateau->lireVue()->getCenter().x < jeu.lireAffichage().getSize()
					.x / 2)
				plateau->bougerPlateau(-5, 0);
			break;
		case Haut:
			if (-plateau->lireVue()->getCenter().y < jeu.lireAffichage().getSize()
					.x / 2)
				plateau->bougerPlateau(0, -5);
			break;
		case Bas:
			if (plateau->lireVue()->getCenter().y < jeu.lireAffichage().getSize()
					.y / 2)
				plateau->bougerPlateau(0, 5);
			break;
		case Case:
			plateau->appuiCase();
			break;
		default:
			break;
	}
}
