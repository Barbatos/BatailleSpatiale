/*
 * GestionnaireSons.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#include "GestionnaireSons.hpp"
#include <iostream>

GestionnaireSons::GestionnaireSons(Ressources* ressources) :
		ressources(ressources), horloge(), phaseDeJeu(false), tempsChangement(0), aChangeIntensite(false)
{
}

GestionnaireSons::~GestionnaireSons()
{
}

void GestionnaireSons::lancerChanson()
{
	if (musique != nullptr)
	{
		musique.get()->setLoop(true);
		if (musique.get()->getStatus() != sf::Music::Playing)
		{
			musique.get()->play();
		}
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

void GestionnaireSons::changerChanson(Ressources::MusicPtr pointeur)
{
	stopperChanson();
	musique = pointeur;
}

Ressources* GestionnaireSons::lireRessources()
{
	return ressources;
}

Ressources::MusicPtr GestionnaireSons::chargerMusique(std::string texte)
{
	return ressources->lireMusique(texte);
}

bool GestionnaireSons::dejaEnCour(Ressources::MusicPtr comparatif)
{
	if (comparatif == musique)
		return true;
	else
		return false;
}

Ressources::MusicPtr GestionnaireSons::lireMusique()
{
	return musique;
}

bool GestionnaireSons::lirePhaseDeJeu()
{
	return phaseDeJeu;
}

void GestionnaireSons::ecrirePhaseDeJeu(bool value)
{
	phaseDeJeu = value;
	horloge.restart();
}

int GestionnaireSons::lireTempsChangement()
{
	return tempsChangement;
}

void GestionnaireSons::ecrireTempsChangement(int value)
{
	tempsChangement = value;
}

void GestionnaireSons::controlerIntensite()
{
	sf::Time timer = horloge.getElapsedTime();
	int minutes = (int) timer.asSeconds() / 60;

	if (minutes >= tempsChangement)
	{
		if (musique->getStatus() == sf::Music::Playing && !aChangeIntensite
				&& musique->getPlayingOffset().asSeconds() >= musique->getDuration().asSeconds()-5)
		{
			horloge.restart();
			aChangeIntensite = true;
			changerChanson(chargerMusique("game_hard.ogg"));
			lancerChanson();
		}

	}
}
