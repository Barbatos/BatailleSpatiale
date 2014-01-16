/*
 * Archive.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Archive.hpp"

#include <fstream>
#include <client/utile/Log.hpp>
#include <client/utile/Utile.hpp>

Archive::Archive(std::string fichier) {
	std::vector<std::string> fichiers;

	lireToc(fichier, fichiers);

	for(std::vector<std::string>::size_type i = 0; i < fichiers.size(); i++) {
		trierFichier(fichiers[i]);
	}
}

Archive::~Archive() {

}

void Archive::lireToc(const std::string cheminToc, std::vector<std::string>& fichiers) {
	std::ifstream entree(cheminToc, std::ifstream::in);

	fichierLog.ajouterLigne("Lecture du fichier " + cheminToc + "\n");

	if(!entree.good())
		Utile::erreur("Archive::lireToc()", "Impossible d'ouvrir " + cheminToc);

	while(!entree.eof()) {
		std::string str;

		std::getline(entree, str);

		if(str[0] != '#' && str != "" && str[0] != ' ') {
			fichiers.push_back(str);
		}
	}

	entree.close();
}

void Archive::trierFichier(std::string fichier) {
	std::string extension = Utile::extension(fichier);

	if(extension == "png")
		images.push_back(fichier);
	else if(extension == "ttf")
		polices.push_back(fichier);
	else if(extension == "wav")
		sons.push_back(fichier);
	else if(extension == "ogg")
		musiques.push_back(fichier);
	else
		fichierLog.ajouterLigne("Extension inconnue : " + fichier + "\n");
}

std::vector<std::string> Archive::lireImages() {
	return(images);
}

std::vector<std::string> Archive::lirePolices() {
	return(polices);
}

std::vector<std::string> Archive::lireSons() {
	return(sons);
}

std::vector<std::string> Archive::lireMusiques() {
	return(musiques);
}
