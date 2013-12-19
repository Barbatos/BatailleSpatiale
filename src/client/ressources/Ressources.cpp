/*
 * Ressources.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Ressources.hpp"

#include "Archive.hpp"

#include <client/utile/Utile.hpp>
#include <client/utile/Log.hpp>

#include <iostream>

/**
 * Constructeur/Destructeur
 */

Ressources::Ressources() :
		volumeSons(0),
		volumeMusiques(0)
{
}

Ressources::~Ressources()
{
}

void Ressources::charger()
{
	sf::Thread thread(&Ressources::threadChargement, this);

	thread.launch();

	Splash::lireInstance().lancer();
}

void Ressources::threadChargement()
{
	Archive archive("ressources/ressources.txt");

	int maxi = archive.lireImages().size() + archive.lirePolices().size() + archive
			.lireSons().size() + archive.lireMusiques().size();

	Splash::lireInstance().changerMaxi(maxi);

	fichierLog.ajouterLigne("Chargement des images :");

	chargerImages(archive.lireImages());

	fichierLog.ajouterLigne("\nChargement des polices :");

	chargerPolices(archive.lirePolices());

	fichierLog.ajouterLigne("\nChargement des sons :");

	chargerSons(archive.lireSons());

	fichierLog.ajouterLigne("\nChargement des musiques :");

	chargerMusiques(archive.lireMusiques());

	fichierLog.ajouterLigne("");

	Splash::lireInstance().fermer();
}

void Ressources::chargerImage(std::string nomImage)
{
	textures.insert(
			std::pair<std::string, sf::Texture>(nomImage, sf::Texture()));

	if (!textures[nomImage].loadFromFile("ressources/images/" + nomImage))
	{
		Utile::erreur("Ressources::chargerImage(" + nomImage + ")",
						"Impossible de charger " + nomImage);
	}

	textures[nomImage].setSmooth(true);

	fichierLog.ajouterLigne("    " + nomImage + " chargée !");
}

void Ressources::chargerImages(std::vector<std::string> fichiers)
{
	for (std::vector<std::string>::size_type i = 0; i < fichiers.size(); i++)
	{
		Splash::lireInstance().changerTexte(fichiers[i]);

		fichierLog.ajouterLigne("    Chargement de " + fichiers[i] + " ...");

		chargerImage(fichiers[i]);

		Splash::lireInstance().changerValeur(
				Splash::lireInstance().lireValeur() + 1);
	}
}

sf::Sprite Ressources::lireImage(std::string nomImage)
{
	fichierLog.ajouterLigne("Recherche de : " + nomImage);

	if (textures.count(nomImage) == 0)
	{
		chargerImage(nomImage);
	}

	return (sf::Sprite(textures[nomImage]));
}

/*
 *		Polices
 */

void Ressources::chargerPolice(std::string nomPolice)
{
	polices.insert(std::pair<std::string, sf::Font>(nomPolice, sf::Font()));

	if (!polices[nomPolice].loadFromFile("ressources/polices/" + nomPolice))
	{
		Utile::erreur("Ressources::chargerPolice(" + nomPolice + ")",
						"Impossible de charger " + nomPolice);
	}

	fichierLog.ajouterLigne("    " + nomPolice + " chargée !");
}

void Ressources::chargerPolices(std::vector<std::string> fichiers)
{
	for (std::vector<std::string>::size_type i = 0; i < fichiers.size(); i++)
	{
		Splash::lireInstance().changerTexte(fichiers[i]);

		fichierLog.ajouterLigne("    Chargement de " + fichiers[i] + " ...");

		chargerPolice(fichiers[i]);

		Splash::lireInstance().changerValeur(
				Splash::lireInstance().lireValeur() + 1);
	}
}

sf::Font& Ressources::lirePolice(std::string nomPolice)
{
	fichierLog.ajouterLigne("Recherche de : " + nomPolice);

	if (polices.count(nomPolice) == 0)
	{
		chargerPolice(nomPolice);
	}

	return (polices[nomPolice]);
}

/*
 *		Sons
 */

void Ressources::chargerSon(std::string nomSon)
{
	sons.insert(
			std::pair<std::string, std::pair<sf::SoundBuffer, sf::Sound>>(
					nomSon,
					std::pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(),
															sf::Sound())));

	if (!sons[nomSon].first.loadFromFile("ressources/sons/" + nomSon))
	{
		Utile::erreur("Ressources::chargerSon(" + nomSon + ")",
						"Impossible de charger " + nomSon);
	}

	sons[nomSon].second.setBuffer(sons[nomSon].first);

	sons[nomSon].second.setVolume(volumeSons);

	fichierLog.ajouterLigne("    " + nomSon + " chargé !");
}

void Ressources::chargerSons(std::vector<std::string> fichiers)
{
	for (std::vector<std::string>::size_type i = 0; i < fichiers.size(); i++)
	{
		Splash::lireInstance().changerTexte(fichiers[i]);

		fichierLog.ajouterLigne("    Chargement de " + fichiers[i] + " ...");

		chargerSon(fichiers[i]);

		Splash::lireInstance().changerValeur(
				Splash::lireInstance().lireValeur() + 1);
	}
}

void Ressources::jouerSon(std::string nomSon)
{
	if (sons.count(nomSon) == 0)
	{
		chargerSon(nomSon);
	}

	sons[nomSon].second.setVolume(volumeSons);

	sons[nomSon].second.play();
}

/*
 *		Musiques
 */

void Ressources::chargerMusique(std::string nomMusique)
{
	musiques.insert(
			std::pair<std::string, MusicPtr>(nomMusique,
												MusicPtr(new sf::Music())));

	if (!musiques[nomMusique]->openFromFile(
			"ressources/musiques/" + nomMusique))
	{
		musiques[nomMusique].reset();

		Utile::erreur("Ressources::chargerMusique(" + nomMusique + ")",
						"Impossible de charger " + nomMusique);
	}

	musiques[nomMusique]->setVolume(volumeMusiques);

	fichierLog.ajouterLigne("    " + nomMusique + " chargée !");
}

void Ressources::chargerMusiques(std::vector<std::string> fichiers)
{
	for (std::vector<std::string>::size_type i = 0; i < fichiers.size(); i++)
	{
		Splash::lireInstance().changerTexte(fichiers[i]);

		fichierLog.ajouterLigne("    Chargement de " + fichiers[i] + " ...");

		chargerMusique(fichiers[i]);

		Splash::lireInstance().changerValeur(
				Splash::lireInstance().lireValeur() + 1);
	}
}

Ressources::MusicPtr Ressources::lireMusique(std::string nomMusique)
{
	fichierLog.ajouterLigne("Recherche de : " + nomMusique);

	if (musiques.count(nomMusique) == 0)
	{
		chargerMusique(nomMusique);
	}

	return (musiques[nomMusique]);
}

/*
 *		Volume
 */

void Ressources::changerVolumeSons(int volume)
{
	volumeSons = volume;

	for (std::pair<std::string, SoundPair> paire : sons)
	{
		sons[paire.first].second.setVolume(volume);
	}
}

void Ressources::changerVolumeMusiques(int volume)
{
	volumeMusiques = volume;

	for (MusicMap::iterator it = musiques.begin(); it != musiques.end(); it++)
	{
		(*it).second->setVolume(volume);
	}
}

void Ressources::changerVolumeGlobal(int volume)
{
	changerVolumeSons(volume);
	changerVolumeMusiques(volume);
}
