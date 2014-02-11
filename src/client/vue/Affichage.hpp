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
class Affichage: public sf::RenderWindow {
private:
	static Affichage* instance;

	/**
	 * \brief Constructeur
	 *
	 * Créé une nouvelle instance d'Affichage
	 */
	Affichage();

public:
	/**
	 * \brief Destructeur
	 *
	 * Détruit une instance précédemment créé d'Affichage
	 */
	virtual ~Affichage();

	/**
	 * \brief Initialise l'affichage
	 */
	static void initialiser();

	/**
	 * \brief Détruit l'affichage
	 */
	static void detruire();

	/**
	 * \brief Créé l'affichage
	 */
	void creer();

	/**
	 * \brief Créé l'affichage avec les paramètres donnés
	 *
	 * \param mode le mode d'affichage
	 * \param titre le titre de la fenêtre
	 * \param style le style de la fenêtre
	 */
	void creer(sf::VideoMode mode, std::string titre, sf::Int32 style);

	/**
	 * \brief Retourne l'instance de l'affichage
	 *
	 * \return l'instance de l'affichage
	 */
	static Affichage& lireInstance();
};

#define affichage Affichage::lireInstance()

#endif /* AFFICHAGE_HPP */
