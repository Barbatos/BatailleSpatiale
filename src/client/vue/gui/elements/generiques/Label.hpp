/*
 * Label.hpp
 *
 *  Created on: 5 oct. 2013
 *      Author: Soinou
 */

#ifndef LABEL_HPP
#define LABEL_HPP

// Includes de la SFML
#include <SFML/Graphics/Text.hpp>

/**
 * \brief Simple label, affichant du texte
 */
class Label : public sf::Text {

public:
	/**
	 * \brief Constructeur
	 *
	 * Créé un nouveau label avec les paramètres donnés
	 *
	 * Constructeur par défaut
	 */
	Label();

	/**
	 * \brief Constructeur
	 *
	 * Créé un nouveau label avec les paramètres donnés
	 *
	 * \param texte le texte à afficher
	 * \param x la position en x
	 * \param y la position en y
	 */
	Label(std::string texte, float x, float y);

	/**
	 * \brief Constructeur
	 *
	 * Créé un nouveau label avec les paramètres donnés
	 *
	 * \param texte le texte à afficher
	 * \param x la position en x
	 * \param y la position en y
	 * \param police la police du label
	 */
	Label(std::string texte, float x, float y, sf::Font& police);

	/**
	 * \brief Destructeur
	 *
	 * Détruit le label précédemment créé
	 */
	virtual ~Label();

	/**
	 * \class Label
	 *
	 * Hérite de sf::Texte, et donc de toutes les fonctions associées.
	 *
	 * Permet juste d'utiliser une police commune à tout les labels et de les initialiser
	 * directement avec une position.
	 *
	 * Exemple d'utilisation :
	 *
	 \code
	 // Initialisé ailleurs (Par le jeu normalement)
	 Affichage affichage;

	 // Créé un label avec pour texte "Je suis un label", en position 100x/50y
	 Label label("Je suis un label", 100, 50);

	 // Dessine le label sur l'Affichage
	 affichage.draw(label);
	 \endcode
	 */
};

#endif /* LABEL_HPP */
