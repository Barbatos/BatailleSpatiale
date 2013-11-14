/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeuMenu.hpp"

#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneJeuMenu::SceneJeuMenu(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 1.5;
	int hauteur = 86 / 1.5;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 7;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.jpg")));

	Bouton* btnretour = new Bouton(Retour, "Retour au jeu", x, y, largeur,
									hauteur);
	Bouton* btnsauvegarder = new Bouton(Sauvegarder, "Sauvegarder la partie", x,
										2 * y, largeur, hauteur);
	Bouton* btncharger = new Bouton(Charger, "Charger une partie", x, 3 * y,
									largeur, hauteur);
	Bouton* btnoptions = new Bouton(Options, "Options", x, 4 * y, largeur,
									hauteur);
	Bouton* btnquitterpartie = new Bouton(QuitterPartie, "Quitter la partie", x,
											5 * y, largeur, hauteur);
	Bouton* btnquitterjeu = new Bouton(QuitterJeu, "Quitter le jeu", x, 6 * y,
										largeur, hauteur);

	ajouter(btnretour);
	ajouter(btnsauvegarder);
	ajouter(btncharger);
	ajouter(btnoptions);
	ajouter(btnquitterpartie);
	ajouter(btnquitterjeu);

	enregistrerSouris(btnretour);
	enregistrerSouris(btnsauvegarder);
	enregistrerSouris(btncharger);
	enregistrerSouris(btnoptions);
	enregistrerSouris(btnquitterpartie);
	enregistrerSouris(btnquitterjeu);
}

SceneJeuMenu::~SceneJeuMenu()
{
}

void SceneJeuMenu::surMessage(int nom, Message message)
{
	switch (message)
	{
		case Clic:
			switch (nom)
			{
				case Retour:
					jeu.changer(Scene::SceneJeu);
					break;
				case QuitterJeu:
					jeu.quitter();
					break;
				case QuitterPartie:
					jeu.changer(Scene::SceneMenuPrincipal);
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
