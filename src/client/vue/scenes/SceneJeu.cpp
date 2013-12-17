/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

<<<<<<< HEAD
#include <client/vue/gui/elements/Image.hpp>
#include <client/vue/gui/elements/Bouton.hpp>
=======
#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/vue/gui/BoutonDeplacementCarte.hpp>
<<<<<<< HEAD
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
=======
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
#include <client/Jeu.hpp>

SceneJeu::SceneJeu(Jeu& jeu) :
		Scene(jeu),
<<<<<<< HEAD
<<<<<<< HEAD
		plateau(&gui, Plateau, 640, 0, 640, 376)
=======
		plateau(Plateau, 0, 0, 640, 376)
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
=======
		plateau(Plateau, 0, 0, 640, 376)
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
{
	float largeur = 300 / 2;
	float hauteur = 86 / 2;

	float x = (jeu.lireAffichage().getSize().x - largeur);
	float y = (jeu.lireAffichage().getSize().y - hauteur);

	new Image(&gui, 100, 0, 0, jeu.lireAffichage().getSize().x,
				jeu.lireAffichage().getSize().y,
				jeu.lireRessources().lireImage("fond.png"));

<<<<<<< HEAD
	new Bouton(&gui, Pause, "Pause", x, y, largeur, hauteur);
	new Bouton(&gui, Droite, ">", jeu.lireAffichage().getSize().x - 50,
				(jeu.lireAffichage().getSize().y - 50) / 2, 50, 50);
	new Bouton(&gui, Gauche, "<", 0, (jeu.lireAffichage().getSize().y - 50) / 2,
				50, 50);
	new Bouton(&gui, Haut, "^", (jeu.lireAffichage().getSize().x - 50) / 2, 0,
				50, 50);
	new Bouton(&gui, Bas, "V", (jeu.lireAffichage().getSize().x - 50) / 2,
				6 * (jeu.lireAffichage().getSize().y) / 7, 50, 50);
=======
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
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
}

SceneJeu::~SceneJeu()
{

}

void SceneJeu::surMessage(int id)
{
	switch (id)
	{
<<<<<<< HEAD
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
=======
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
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
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
}
