/*
 * Scene.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Scene.hpp"

// On inclut les déclarations des classes manquantes
#include <client/Jeu.hpp>

Scene::Scene(Jeu& jeu) :
	jeu(jeu),
	gui(&jeu.lireAffichage(), this) {
}

Scene::~Scene() {
}

void Scene::actualiser() {
	gui.actualiser();
}

void Scene::afficher() {
	gui.afficher();
}

void Scene::traiter(sf::Event& evenement) {
	gui.traiter(evenement);
}

Jeu& Scene::lireJeu() {
	return jeu;
}

Gui& Scene::lireGui() {
	return gui;
}
