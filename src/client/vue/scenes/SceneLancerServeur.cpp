/*
 * SceneLancerServeur.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Barbatos
 */

#include "SceneLancerServeur.hpp"

#include <client/vue/gui/ZoneTexte.hpp>
#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneLancerServeur::SceneLancerServeur(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 5;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.png")));


	port = new ZoneTexte(Port, x, 2 * y, largeur, hauteur);

	Bouton* btnserveur = new Bouton(Serveur, "Lancer le serveur", x, 3 * y, largeur,
									hauteur);

	Bouton* btnretour = new Bouton(Retour, "Retour", x, 4 * y, largeur,
									hauteur);

	ajouter(port);
	ajouter(btnserveur);
	ajouter(btnretour);

	enregistrerSouris(port);
	enregistrerSouris(btnserveur);
	enregistrerSouris(btnretour);

	enregistrerClavier(port);
}

SceneLancerServeur::~SceneLancerServeur()
{
}

void SceneLancerServeur::surMessage(int, Scene::Message)
{
	/*switch (message)
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
				default:
					break;
			}
			break;
		case Entre:
			break;
		case Sort:
			break;
	}*/
}
