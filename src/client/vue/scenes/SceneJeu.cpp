/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/vue/gui/elements/BoutonDeplacementCarte.hpp>

#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu) :
		Scene(jeu)
{
	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	plateau = AffichagePlateau::Ptr(
			new AffichagePlateau(&gui, Plateau, 30, 30, 580, 316));

	details = AffichageDetails::Ptr(
			new AffichageDetails(&gui, Details, 0, 0, 100, 50));

	new BoutonDeplacementCarte(&gui, Droite,
								jeu.lireAffichage().getSize().x - 30, 30, 30,
								jeu.lireAffichage().getSize().y - 60);
	new BoutonDeplacementCarte(&gui, Gauche, 0, 30, 30,
								jeu.lireAffichage().getSize().y - 60);
	new BoutonDeplacementCarte(&gui, Haut, 30, 0,
								jeu.lireAffichage().getSize().x - 60, 30);
	new BoutonDeplacementCarte(&gui, Bas, 30, 316,
								jeu.lireAffichage().getSize().x - 60, 30);
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
			plateau->bougerPlateau(5, 0);
			break;
		case Gauche:
			plateau->bougerPlateau(-5, 0);
			break;
		case Haut:
			plateau->bougerPlateau(0, -5);
			break;
		case Bas:
			plateau->bougerPlateau(0, 5);
			break;
		default:
			break;
	}
}
