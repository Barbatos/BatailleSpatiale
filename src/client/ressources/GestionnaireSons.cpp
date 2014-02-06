/*
 * GestionnaireSons.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#include "GestionnaireSons.hpp"

GestionnaireSons::GestionnaireSons(Ressources& ressources) : ressources(ressources)
{
	horloge = new sf::Clock();

	//Par défaut on charge la musique du menu
	musique = ressources.lireMusique("menu_soundtrack.ogg");

}

GestionnaireSons::~GestionnaireSons()
{
	// TODO Auto-generated destructor stub
}

