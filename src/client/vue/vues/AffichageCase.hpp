/*
 * AffichageCase.hpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGECASE_HPP
#define AFFICHAGECASE_HPP

// Includes de la libstd
#include <memory>

// Include du 'pack' vue
#include "VuesPack.hpp"

typedef std::shared_ptr<sf::View> VuePtr;

/**
 * \brief Représente l'affichage d'une case du plateau
 */
class AffichageCase :
	public Element
{
	private:
		/**
		 * \brief L'image affichée sur la case
		 */
		sf::Sprite image;

		/**
		 * \brief Le fond de la case
		 */
		sf::CircleShape fond;

		/**
		 * \brief La position associée à la case
		 */
		Position position;

		/**
		 * \brief La vue qui contient la case
		 */
		VuePtr vuePlateau;

		/**
		 * \brief Si la case est survolée
		 */
		bool survole;

		/**
		 * \brief Si la case est selectionnée
		 */
		bool selectionne;

	public:
		typedef std::unique_ptr<AffichageCase> Ptr;

		/**
		 * \brief Constructeur
		 */
		AffichageCase(Gui* gui, int id, float x, float y, float taille,
			Position position, sf::View* vuePlateau);

		/**
		 * \brief Destructeur
		 */
		virtual ~AffichageCase();

		// Héritées d'Element
		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
};

#endif /* AFFICHAGECASE_HPP */
