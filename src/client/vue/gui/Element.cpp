/*
 * element.cpp
 *
 *  Created on: 6 oct. 2013
 *      Author: Soinou
 */

#include "Element.hpp"

Element::Element(int nom, int x, int y, int largeur, int hauteur) : nom(nom), zone(x, y, largeur, hauteur), parent(nullptr)
{

}

Element::Element(int nom, sf::FloatRect zone) : nom(nom), zone(zone), parent(nullptr)
{

}

Element::~Element()
{
	parent.release();
}

void Element::changerParent(Scene* parent)
{
	this->parent = ScenePtr(parent);
}

void Element::envoyerMessage(Scene::Message message)
{
	parent->surMessage(nom, message);
}
