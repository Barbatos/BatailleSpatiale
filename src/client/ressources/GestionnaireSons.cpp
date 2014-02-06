/*
 * GestionnaireSons.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#include "GestionnaireSons.hpp"

GestionnaireSons::GestionnaireSons(Ressources* ressources) :
		ressources(ressources), horloge()
{
	//Par défaut on charge la musique du menu
	musique = ressources->lireMusique("menu_soundtrack.ogg");

}

GestionnaireSons::~GestionnaireSons()
{
	// TODO Auto-generated destructor stub
}

void GestionnaireSons::lancerChanson()
{
	if (musique != nullptr)
	{
		musique.get()->setLoop(true);
		if (musique.get()->getStatus() != sf::Music::Playing)
			musique.get()->play();
	}
}

void GestionnaireSons::stopperChanson()
{
	if (musique != nullptr)
	{
		if (musique.get()->getStatus() == sf::Music::Playing)
			musique.get()->stop();
	}
}

void GestionnaireSons::playPauseChanson()
{
	if (musique != nullptr)
	{
		if (musique.get()->getStatus() == sf::Music::Playing)
			stopperChanson();
		else
			lancerChanson();
	}
}

