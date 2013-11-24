/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "SceneMenuPrincipal.hpp"

#include <client/vue/gui/Image.hpp>
#include <client/vue/gui/Animation.hpp>
#include <client/vue/gui/Bouton.hpp>
#include <client/Jeu.hpp>

SceneMenuPrincipal::SceneMenuPrincipal(Jeu& jeu) :
		Scene(jeu)
{
	int largeur = 300 / 2;
	int hauteur = 86 / 2;

	int x = (jeu.lireAffichage().getSize().x - largeur) / 2;

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 5;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.png")));

	Bouton* btnsolo = new Bouton(Solo, "Partie Solo", x, y, largeur, hauteur);
	Bouton* btnmulti = new Bouton(Multi, "Partie Multi", x, 2 * y, largeur,
									hauteur);
	Bouton* btnquitter = new Bouton(Quitter, "Quitter le jeu", x, 4 * y,
									largeur, hauteur);
	Bouton* btnmusique = new Bouton(Musique, "Jouer musique", 0, 0, largeur,
									hauteur);
	Bouton* btnoptions = new Bouton(Options,"Options",x,3 * y,largeur,hauteur);

	ajouter(btnsolo);
	ajouter(btnmulti);
	ajouter(btnquitter);
	ajouter(btnmusique);
	ajouter(btnoptions);

	enregistrerSouris(btnsolo);
	enregistrerSouris(btnmulti);
	enregistrerSouris(btnquitter);
	enregistrerSouris(btnmusique);
	enregistrerSouris(btnoptions);

	jeu.lireRessources().changerVolumeGlobal(10);

	musique = jeu.lireRessources().lireMusique("Clearness.ogg");

	ajouter(new Animation(999, 10, 100, 240, 240, 23, jeu.lireRessources().lireImage("test.png")));
}

SceneMenuPrincipal::~SceneMenuPrincipal()
{

}

void SceneMenuPrincipal::surMessage(int nom, Scene::Message message)
{
	switch (message)
	{
		case Clic:
			switch (nom)
			{
				case Solo:
					jeu.changer(Scene::SceneMenuSolo);
					break;
				case Multi:
					jeu.changer(Scene::SceneMenuMultijoueur);
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
			break;
		case Entre:
			break;
		case Sort:
			break;
	}
}
