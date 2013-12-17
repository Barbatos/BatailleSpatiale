/*
 * Scene.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Scene.hpp"

// On inclut les déclarations des classes manquantes
#include <client/Jeu.hpp>
#include <client/vue/gui/Element.hpp>
#include <client/vue/gui/ElementSouris.hpp>
#include <client/vue/gui/ElementClavier.hpp>

#include <client/vue/Affichage.hpp>

Scene::Scene(Jeu& jeu) :
		jeu(jeu),
		gui(&jeu.lireAffichage(), this)
{
}

Scene::~Scene()
{
}

void Scene::actualiser()
{
	gui.actualiser();
}

void Scene::afficher()
{
	gui.afficher();
}

void Scene::traiter(sf::Event& evenement)
{
	gui.traiter(evenement);
}

Jeu& Scene::lireJeu()
{
	return jeu;
}

Gui& Scene::lireGui()
{
	return gui;
}
