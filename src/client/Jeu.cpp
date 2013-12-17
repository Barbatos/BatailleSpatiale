/*
 * Jeu.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Jeu.hpp"

#include <iostream>
#include <client/vue/vues/AffichageDetails.hpp>

#define FPS 60
#define TEMPS_FRAME 1000/FPS

Jeu::Jeu() :
		affichage(),
		modele(),
		controleur(modele),
		scene(nullptr),
		ressources(),
		horloge(),
		reseau(nullptr)
{
	changer(Scene::SceneMenuPrincipal);
	reseau = ReseauPtr(new ReseauClient());
}

Jeu::~Jeu()
{
	if (scene != nullptr)
		scene.release();

	if (reseau != nullptr)
		reseau.release();
}

void Jeu::changer(Scene::Type nouvelleScene)
{
	if (scene != nullptr)
		scene.release();

	switch (nouvelleScene)
	{
		case Scene::SceneMenuPrincipal:
			scene = Scene::Ptr(new SceneMenuPrincipal(*this));
			break;
		case Scene::SceneJeu:
			scene = Scene::Ptr(new SceneJeu(*this));
			break;
		case Scene::SceneJeuMenu:
			scene = Scene::Ptr(new SceneJeuMenu(*this));
			break;
		case Scene::SceneJeuOptions:
			scene = Scene::Ptr(new SceneJeuOptions(*this));
			break;
		case Scene::SceneMenuSolo:
			if (reseau->getActif())
				scene = Scene::Ptr(new SceneJeu(*this));
			else
				scene = Scene::Ptr(new SceneMenuSolo(*this));
			break;
		case Scene::SceneMenuMultijoueur:
			if (reseau->getActif())
				scene = Scene::Ptr(new SceneJeu(*this));
			else
				scene = Scene::Ptr(new SceneMenuMultijoueur(*this));
			break;
		case Scene::SceneOptionsMenu:
			scene = Scene::Ptr(new SceneOptionsMenu(*this));
			break;

		case Scene::SceneLancerServeur:
			scene = Scene::Ptr(new SceneLancerServeur(*this));
			break;

		default:
			scene = Scene::Ptr(new SceneMenuPrincipal(*this));
			break;
	}
}

void Jeu::threadReseau()
{
	while (true)
	{
		reseau->TraiterPaquetServeur();
		sf::sleep(sf::milliseconds(10));
	}
}

void Jeu::lancer()
{

	sf::Event evenement;
	int message;
	sf::Thread reseauThread(&Jeu::threadReseau, this);

	reseauThread.launch();

	while (affichage.isOpen())
	{
		while (affichage.pollEvent(evenement))
		{
			if (evenement.type == sf::Event::Closed)
				affichage.close();

			scene->traiter(evenement);
		}

		while (scene->lireGui().obtenirMessage(&message))
		{
			scene->surMessage(message);
		}

		affichage.clear();

		scene->actualiser();

		scene->afficher();

		affichage.display();
	}

	reseauThread.terminate();
}

void Jeu::quitter()
{
	affichage.close();
}

Affichage& Jeu::lireAffichage()
{
	return (affichage);
}

Plateau& Jeu::lirePlateau()
{
	return (modele);
}

Controleur& Jeu::lireControleur()
{
	return (controleur);
}

Ressources& Jeu::lireRessources()
{
	return (ressources);
}

ReseauPtr& Jeu::lireReseau()
{
	return (reseau);
}
