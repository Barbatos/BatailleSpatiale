/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneMenuSolo.hpp"

#include <client/vue/gui/ZoneTexte.hpp>
#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuSolo::SceneMenuSolo(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 5;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.png")));

	ip = new ZoneTexte(Ip, x, y, largeur, hauteur);

	port = new ZoneTexte(Port, x, 2 * y, largeur, hauteur);

	Bouton* btnsolo = new Bouton(Solo, "Lancer partie", x, 3 * y, largeur,
									hauteur);

	Bouton* btnretour = new Bouton(Retour, "Retour", x, 4 * y, largeur,
									hauteur);

	ajouter(ip);
	ajouter(port);
	ajouter(btnsolo);
	ajouter(btnretour);

	enregistrerSouris(ip);
	enregistrerSouris(port);
	enregistrerSouris(btnsolo);
	enregistrerSouris(btnretour);

	enregistrerClavier(ip);
	enregistrerClavier(port);
}

SceneMenuSolo::~SceneMenuSolo()
{
}

void SceneMenuSolo::surMessage(int nom, Scene::Message message)
{
	switch (message)
	{
		case Clic:
			switch (nom)
			{
				case Solo:
					jeu.lireReseau()->ConnexionServeur(
						ip->lireTexte(), atoi(port->lireTexte().c_str()));

					if (jeu.lireReseau()->getActif())
						jeu.changer(Scene::SceneJeu);
					break;
				case Retour:
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
