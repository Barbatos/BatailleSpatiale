/*
 * Affichage.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <SFML/Graphics.hpp>

/**
 * \brief Correspond à la fenêtre associée au jeu
 *
 * Représente la fenêtre qui affiche le jeu
 */
class Affichage :
	public sf::RenderWindow {
public:
	/**
	 * \brief Constructeur
	 *
	 * Créé une nouvelle instance d'Affichage
	 */
	Affichage();

	/**
	 * \brief Destructeur
	 *
	 * Détruit une instance précédemment créé d'Affichage
	 */
	virtual ~Affichage();

	/**
	 * \brief Créé l'affichage
	 */
	void creer();
};

#endif /* AFFICHAGE_HPP */
