/*
 * Utile.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Utile.hpp"

#include "Log.hpp"

#include <stdlib.h>
#include <time.h>

namespace Utile {
void erreur(string endroit, string erreur) {
	fichierLog.ajouterLigne("Erreur à " + endroit + " : " + erreur);

	exit(-1);
}

string nomFichier(const string& cheminFichier) {
	size_t fin = cheminFichier.find_last_of('.');

	size_t debut = cheminFichier.find_last_of('/');

	if (fin == string::npos)
		fin = cheminFichier.length();

	if (debut == string::npos)
		debut = 0;
	else
		debut++;

	return (cheminFichier.substr(debut, fin - debut));
}

string extension(const string& nomFichier) {
	unsigned endroit = nomFichier.find_last_of('.');

	return (nomFichier.substr(endroit + 1));
}

string dateActuelle() {
	time_t courant = time(0);

	struct tm tstruct;

	char buffer[80];

	tstruct = *localtime(&courant);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &tstruct);

	return (buffer);
}

void redimensionnerImage(sf::Sprite& image, float largeur, float hauteur,
                         bool proportions) {
	float largeurImage = image.getLocalBounds().width;
	float hauteurImage = image.getLocalBounds().height;
	float coeffX;
	float coeffY;

	coeffX = largeur / largeurImage;
	coeffY = hauteur / hauteurImage;

	if (hauteur < largeur && proportions)
		image.scale(coeffX, coeffX);
	else if (proportions)
		image.scale(coeffY, coeffY);
	else
		image.scale(coeffX, coeffY);
}

std::string convertir(TypeVaisseau type) {
	switch (type) {
	case TypeVaisseau::Inexistant:
		return "Inexistant";
	case TypeVaisseau::Constructeur:
		return "Constructeur";
	case TypeVaisseau::Bombardier:
		return "Bombardier";
	case TypeVaisseau::Chasseur:
		return "Chasseur";
	case TypeVaisseau::Croiseur:
		return "Croiseur";
	case TypeVaisseau::Destructeur:
		return "Destructeur";
	case TypeVaisseau::ChasseurLourd:
		return "Chasseur Lourd";
	case TypeVaisseau::Traqueur:
		return "Traqueur";
	case TypeVaisseau::Leger:
		return "Léger";
	default:
		return "";
	}
}

std::string convertir(TypeBatiment type) {
	switch (type) {
	case TypeBatiment::Base:
		return "Base";
	default:
		return "";
	}
}

std::string convertir(TypeEvenement type) {
	switch (type) {
	case TypeEvenement::ChampMeteor:
		return "Champ de Météore";
	case TypeEvenement::Epave:
		return "Epave";
	case TypeEvenement::InfluenceTrouNoir:
		return "Influence trou noir";
	case TypeEvenement::NuageGaz:
		return "Nuage de gaz";
	case TypeEvenement::StationSpatialeAbandonnee:
		return "Station spatiale abandonnée";
	default:
		return "";
	}
}
}
