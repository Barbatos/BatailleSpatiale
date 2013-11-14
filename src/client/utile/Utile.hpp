/*
 * Utile.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef UTILE_HPP
#define UTILE_HPP

// Includes de la libstd
#include <string>

// Includes de la SFML
#include <SFML/Graphics.hpp>

/**
 * \brief Boîte à outils
 *
 * Contient de nombreuses fonctions utiles
 */
namespace Utile
{
	using namespace std;

	/**
	 * \brief Génère une erreur
	 *
	 * Permet d'afficher l'erreur donnée en paramètre et de quitter le programme immédiatement
	 *
	 * \param endroit l'endroit où s'est passée l'erreur
	 * \param erreur simple message décrivant l'erreur
	 */
	void erreur(string endroit, string erreur);

	/**
	 * \brief Donne le nom du fichier à partir d'un chemin
	 *
	 * Permet de trouver le nom du fichier à partir d'un chemin, et de le renvoyer.
	 *
	 * Exemple : C:/exemple/de/chemin/exemple/de/fichier.cpp -> fichier.cpp
	 *
	 * \param cheminFichier le chemin à tester
	 * \return le nom du fichier contenu dans le chemin
	 */
	string nomFichier(const string& cheminFichier);

	/**
	 * \brief Donne l'extension du fichier à partir d'un chemin/nom
	 *
	 * Permet de trouver l'extension à partir d'un chemin ou d'un nom de fichier, et de le renvoyer.
	 *
	 * Exemple : nomDeFichier.extension -> extension
	 *
	 * \param cheminFichier le chemin ou le nom du fichier
	 * \return l'extension du fichier donné
	 */
	string extension(const string& cheminFichier);

	/**
	 * \brief Renvoie la date actuelle
	 *
	 * Renvoie une chaîne de caractère contenant la date actuelle sous le format AAAA-MM-JJ-hh:mm:ss
	 *
	 * \return la date actuelle dans une chaîne de caractère
	 */
	string dateActuelle();

	/**
	 * \brief Redimensionne l'image donnée en paramètre
	 *
	 * Redimensionne l'image donnée, en gardant ou non les proportions
	 *
	 * \param image l'image à redimensionner
	 * \param largeur la nouvelle largeur
	 * \param hauteur la nouvelle hauteur
	 * \param proportions si les proportions doivent être gardées ou non
	 */
	void redimensionnerImage(sf::Sprite& image, float largeur, float hauteur,
		bool proportions);
}
;

#endif /* UTILE_HPP_ */
