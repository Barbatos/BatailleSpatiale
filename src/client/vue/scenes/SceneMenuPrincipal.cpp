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

	int y = (jeu.lireAffichage().getSize().y - hauteur) / 6;

	ajouter(new Image(100, 0, 0, jeu.lireAffichage().getSize().x,
						jeu.lireAffichage().getSize().y,
						jeu.lireRessources().lireImage("fond.png")));

	Bouton* btnsolo = new Bouton(Solo, "Partie Solo", x, y, largeur, hauteur);
	Bouton* btnmulti = new Bouton(Multi, "Partie Multi", x, 2 * y, largeur,
									hauteur);
	Bouton* btnserveur = new Bouton(Serveur, "Lancer un serveur", x, 3 * y, largeur, hauteur);
	Bouton* btnquitter = new Bouton(Quitter, "Quitter le jeu", x, 5 * y,
									largeur, hauteur);
	Bouton* btnmusique = new Bouton(Musique, "Jouer musique", 0, 0, largeur,
									hauteur);
	Bouton* btnoptions = new Bouton(Options,"Options",x,4 * y,largeur,hauteur);

	ajouter(btnsolo);
	ajouter(btnmulti);
	ajouter(btnserveur);
	ajouter(btnquitter);
	ajouter(btnmusique);
	ajouter(btnoptions);

	enregistrerSouris(btnsolo);
	enregistrerSouris(btnmulti);
	enregistrerSouris(btnserveur);
	enregistrerSouris(btnquitter);
	enregistrerSouris(btnmusique);
	enregistrerSouris(btnoptions);

	jeu.lireRessources().changerVolumeGlobal(10);

	musique = jeu.lireRessources().lireMusique("Clearness.ogg");

	ajouter(new Animation(999, 100, 100, 240, 240, true, jeu.lireRessources().lireImage("Environnement/comete2.png")));
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
				case Serveur:
					jeu.changer(Scene::SceneLancerServeur);
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
