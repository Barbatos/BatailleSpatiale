/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneMenuSolo.hpp"

#include <client/vue/gui/elements/ZoneTexte.hpp>
#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuSolo::SceneMenuSolo(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 5;

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

	ip = new ZoneTexte(&gui, Ip, x, y, largeur, hauteur, "IP");

	port = new ZoneTexte(&gui, Port, x, 2 * y, largeur, hauteur, "Port");

	new Bouton(&gui, Solo, "Lancer partie", x, 3 * y, largeur, hauteur);

	new Bouton(&gui, Retour, "Retour", x, 4 * y, largeur, hauteur);
}

SceneMenuSolo::~SceneMenuSolo()
{
}

void SceneMenuSolo::surMessage(int id)
{
	switch (id)
	{
<<<<<<< HEAD
		case Solo:
			//jeu.lireReseau()->ConnexionServeur(
			//ip->lireTexte(), atoi(port->lireTexte().c_str()));

			//if (jeu.lireReseau()->getActif())
			jeu.changer(Scene::SceneJeu);
=======
		case Clic:
			switch (nom)
			{
				case Solo:
					jeu.connexionServeur(ip->lireTexte(), atoi(port->lireTexte().c_str()));
					break;
				case Retour:
					jeu.changer(Scene::SceneMenuPrincipal);
					break;
				default:
					break;
			}
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
			break;
		case Retour:
			jeu.changer(Scene::SceneMenuPrincipal);
			break;
		default:
			break;
	}
}
