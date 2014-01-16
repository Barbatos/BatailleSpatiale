/*
 * Log.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Log.hpp"
#include "Utile.hpp"

#define FICHIER "BattleStar.log"

#include <iostream>

Log Log::instance;

Log::Log() {
	fichier = OutputStreamPtr(new std::ofstream(FICHIER, std::ios::in | std::ios::app));

	if(fichier->good())
		*fichier
		        << "##################################################"
		        << std::endl
		        << Utile::dateActuelle()
		        << std::endl
		        << std::endl;
	else
		Utile::erreur("initialiserLog()", "Impossible d'ouvrir le fichier BattleStar.log");
}

Log::~Log() {

}

Log& Log::lireInstance() {
	return instance;
}

void Log::ajouterLigne(std::string ligne) {
	if(fichier->good()) {
		*fichier << ligne << std::endl;
	}
}
