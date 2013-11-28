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
						jeu.lireRessources().lireImage("fond.png")));

	Bouton* btnpause = new Bouton(Pause, "Pause", x, y, largeur, hauteur);
	Bouton* btndroite = new Bouton(Droite, ">",
									jeu.lireAffichage().getSize().x - 50,
									(jeu.lireAffichage().getSize().y - 50) / 2,
									50, 50);
	Bouton* btngauche = new Bouton(Gauche, "<", 0,
									(jeu.lireAffichage().getSize().y - 50) / 2,
									50, 50);
	Bouton* btnhaut = new Bouton(Haut, "^",
									(jeu.lireAffichage().getSize().x - 50) / 2,
									0, 50, 50);
	Bouton* btnbas = new Bouton(Bas, "V",
								(jeu.lireAffichage().getSize().x - 50) / 2,
								6 * (jeu.lireAffichage().getSize().y) / 7, 50,
								50);

	ajouter(btnpause);
	ajouter(btndroite);
	ajouter(btngauche);
	ajouter(btnhaut);
	ajouter(btnbas);
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
			break;
		case Entre:
			break;
		case Sort:
			break;
		default:
			break;
	}
}
