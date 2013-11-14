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

Scene::Scene(Jeu& jeu) :
		jeu(jeu), elements(), souris(), clavier()
{

}

Scene::~Scene()
{
	// On détruit tout les éléments de la scène (Sécurité en plus)

	for (std::vector<ElementPtr>::iterator it = elements.begin();
			it != elements.end(); it++)
		(*it).reset();

	for (std::vector<SourisPtr>::iterator it = souris.begin();
			it != souris.end(); it++)
		(*it).reset();

	for (std::vector<ClavierPtr>::iterator it = clavier.begin();
			it != clavier.end(); it++)
		(*it).reset();
}

void Scene::ajouter(Element* element)
{
	// On indique à l'élément un pointeur vers la scène actuelle
	element->changerParent(this);

	// On ajoute l'élément à la scène
	this->elements.push_back(ElementPtr(element));

	// On initialise l'élément
	element->initialiser();
}

void Scene::enregistrerSouris(ElementSouris* souris)
{
	// On ajoute l'élément à la scène
	this->souris.push_back(SourisPtr(souris));
}

void Scene::enregistrerClavier(ElementClavier* clavier)
{
	// On ajoute l'observateur à la scène
	this->clavier.push_back(ClavierPtr(clavier));
}

void Scene::actualiser(float delta)
{
	// On actualise tout les éléments de la scène
	for (std::vector<ElementPtr>::iterator it = elements.begin();
			it != elements.end(); it++)
		(*it)->actualiser(delta);
}

void Scene::afficher()
{
	// On affiche tout les éléments de la scène

	for (std::vector<ElementPtr>::iterator it = elements.begin();
			it != elements.end(); it++)
		(*it)->afficher(jeu.lireAffichage());
}

void Scene::traiter(sf::Event& evenement)
{
	// Selon l'évènement, on l'envoie aux bons éléments

	switch (evenement.type)
	{
		case sf::Event::MouseButtonPressed:
			for (std::vector<SourisPtr>::iterator it = souris.begin();
					it != souris.end(); it++)
				(*it)->surPressionBoutonSouris(evenement.mouseButton);
			break;
		case sf::Event::MouseButtonReleased:
			for (std::vector<SourisPtr>::iterator it = souris.begin();
					it != souris.end(); it++)
				(*it)->surRelachementBoutonSouris(evenement.mouseButton);
			break;
		case sf::Event::MouseMoved:
			for (std::vector<SourisPtr>::iterator it = souris.begin();
					it != souris.end(); it++)
				(*it)->surMouvementSouris(evenement.mouseMove);
			break;
		case sf::Event::MouseWheelMoved:
			for (std::vector<SourisPtr>::iterator it = souris.begin();
					it != souris.end(); it++)
				(*it)->surMoletteSouris(evenement.mouseWheel);
			break;
		case sf::Event::KeyPressed:
			for (std::vector<ClavierPtr>::iterator it = clavier.begin();
					it != clavier.end(); it++)
				(*it)->surRelachementToucheClavier(evenement.key);
			break;
		case sf::Event::KeyReleased:
			for (std::vector<ClavierPtr>::iterator it = clavier.begin();
					it != clavier.end(); it++)
				(*it)->surPressionToucheClavier(evenement.key);
			break;
		case sf::Event::TextEntered:
			for (std::vector<ClavierPtr>::iterator it = clavier.begin();
					it != clavier.end(); it++)
				(*it)->surTexteClavier(evenement.text);
			break;
		default:
			break;
	}
}

Jeu& Scene::lireJeu()
{
	return jeu;
}
