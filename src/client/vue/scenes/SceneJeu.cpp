/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/vue/gui/BoutonDeplacementCarte.hpp>
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
						jeu.lireRessources().lireImage("fond.png")));

	Bouton* btnpause = new Bouton(Pause, "Pause", x, y, largeur, hauteur);
	BoutonDeplacementCarte* btndroite = new BoutonDeplacementCarte(Droite,
									jeu.lireAffichage().getSize().x - 30,
									30,
									30,
									jeu.lireAffichage().getSize().y - 60);
	BoutonDeplacementCarte* btngauche = new BoutonDeplacementCarte(Gauche,
									0,
									30,
									30,
									jeu.lireAffichage().getSize().y - 60);
	BoutonDeplacementCarte* btnhaut = new BoutonDeplacementCarte(Haut,
									30,
									0,
									jeu.lireAffichage().getSize().x - 60,
									30);
	BoutonDeplacementCarte* btnbas = new BoutonDeplacementCarte(Bas,
								30,
								jeu.lireAffichage().getSize().y - 30,
								jeu.lireAffichage().getSize().x - 60,
								30);

	ajouter(btndroite);
	ajouter(btngauche);
	ajouter(btnhaut);
	ajouter(btnbas);
	ajouter(btnpause);
	ajouter(&plateau);

	enregistrerSouris(btnpause);
	enregistrerSouris(btndroite);
	enregistrerSouris(btngauche);
	enregistrerSouris(btnhaut);
	enregistrerSouris(btnbas);
	enregistrerSouris(&plateau);
	enregistrerClavier(&plateau);
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
				case Droite:
					plateau.bougerPlateau(3, 0);
					break;
				case Gauche:
					plateau.bougerPlateau(-3, 0);
					break;
				case Haut:
					plateau.bougerPlateau(0, -3);
					break;
				case Bas:
					plateau.bougerPlateau(0, 3);
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
