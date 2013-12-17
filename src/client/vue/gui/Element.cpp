/*
 * Element.cpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#include "Element.hpp"

#include "Gui.hpp"

Element::Element(Gui* gui, int id) :
		id(id),
		gui(gui),
		souris(false),
		clavier(false),
		observateurSouris(nullptr),
		observateurClavier(nullptr),
		survol(false),
		appui(false)
{
	gui->ajouter(Ptr(this));
}

Element::~Element()
{
	if (gui != nullptr)
		delete gui;

	observateurSouris.reset();

	observateurClavier.reset();
}

ObservateurSouris::Ptr Element::lireSouris()
{
	return observateurSouris;
}

ObservateurClavier::Ptr Element::lireClavier()
{
	return observateurClavier;
}

void Element::enregistrerSouris(ObservateurSouris::Ptr observateur)
{
	if (observateur == nullptr)
		return;

	observateurSouris = observateur;
	souris = true;
}
void Element::enregistrerClavier(ObservateurClavier::Ptr observateur)
{
	if (observateur == nullptr)
		return;

	observateurClavier = observateur;
	clavier = true;
}

bool Element::observeSouris()
{
	return souris;
}

bool Element::observeClavier()
{
	return clavier;
}

int Element::lireId()
{
	return id;
}

Gui* Element::lireGui()
{
	return gui;
}

void Element::ecrireId(int id)
{
	this->id = id;
}

void Element::ecrireGui(Gui* gui)
{
	this->gui = gui;
}

sf::Vector2f Element::lireTaille()
{
	return taille;
}

sf::Vector2f Element::lirePosition()
{
	return position;
}

void Element::ecrireTaille(sf::Vector2f taille)
{
	this->taille = taille;
}

void Element::ecrireTaille(float largeur, float hauteur)
{
	ecrireTaille(sf::Vector2f(largeur, hauteur));
}

void Element::ecrirePosition(sf::Vector2f position)
{
	this->position = position;
}

void Element::ecrirePosition(float x, float y)
{
	ecrirePosition(sf::Vector2f(x, y));
}

void Element::ecrireZone(sf::FloatRect zone)
{
	ecrirePosition(zone.left, zone.top);
	ecrireTaille(zone.width, zone.height);
}

void Element::ecrireSurvol(bool survol)
{
	this->survol = survol;
}

void Element::ecrireAppui(bool appui)
{
	this->appui = appui;
}

bool Element::lireSurvol()
{
	return survol;
}

bool Element::lireAppui()
{
	return appui;
}

void Element::envoyerMessage()
{
	gui->ajouterMessage(id);
}
