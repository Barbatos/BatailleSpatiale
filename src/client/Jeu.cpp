/*
 * Jeu.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Jeu.hpp"

#include <iostream>
#include <client/vue/gui/Bouton.hpp>
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
	reseauActif = false;
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
			scene = ScenePtr(new SceneMenuPrincipal(*this));
			break;
		case Scene::SceneJeu:
			scene = ScenePtr(new SceneJeu(*this));
			break;
		case Scene::SceneJeuMenu:
			scene = ScenePtr(new SceneJeuMenu(*this));
			break;
		case Scene::SceneJeuOptions:
			scene = ScenePtr(new SceneJeuOptions(*this));
			break;
		case Scene::SceneMenuSolo:
			if (reseau->getActif())
				scene = ScenePtr(new SceneJeu(*this));
			else
				scene = ScenePtr(new SceneMenuSolo(*this));
			break;
		case Scene::SceneMenuMultijoueur:
			if (reseau->getActif())
				scene = ScenePtr(new SceneJeu(*this));
			else
				scene = ScenePtr(new SceneMenuMultijoueur(*this));
			break;
		case Scene::SceneOptionsMenu:
			scene = ScenePtr(new SceneOptionsMenu(*this));
			break;

		case Scene::SceneLancerServeur:
			scene = ScenePtr(new SceneLancerServeur(*this));
			break;
			
		default:
			scene = ScenePtr(new SceneMenuPrincipal(*this));
			break;
	}
}

void Jeu::connexionServeur(string ip, unsigned short port){
	reseau->setIp(ip);
	reseau->setPort(port);
}

void Jeu::lancer()
{
	sf::Event evenement;
	sf::Time precedent;
	long delta;
	long attente;

	reseau->lancerReseau();

	while (affichage.isOpen())
	{
		sf::Time nouveau = horloge.getElapsedTime();

		delta = (nouveau - precedent).asMilliseconds();

		precedent = nouveau;

		if(reseau->getActif() && !reseauActif){
			reseauActif = true;
			changer(Scene::SceneJeu);
		}

		while (affichage.pollEvent(evenement))
		{
			if (evenement.type == sf::Event::Closed)
				affichage.close();

			scene->traiter(evenement);
		}

		affichage.clear();

		scene->actualiser(delta);

		scene->afficher();

		affichage.display();

		attente = TEMPS_FRAME - (horloge.getElapsedTime() - nouveau)
				.asMilliseconds();

		if (attente > 0)
			sf::sleep(sf::milliseconds(attente));
	}

	reseau->fermerReseau();
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
