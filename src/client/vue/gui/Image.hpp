/*
 * Image.hpp
 *
 *  Created on: 12 nov. 2013
 *      Author: Soinou
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SFML/Graphics.hpp>

#include "Element.hpp"

/**
 * \brief Simple image à afficher
 *
 * \see Element
 */
class Image :
	public Element
{
	private:
		/**
		 * \brief Le sprite de l'image
		 */
		sf::Sprite sprite;

	public:
		/**
		 * \brief Constructeur
		 *
		 * \param nom le nom de l'image
		 * \param x la position en x de l'image
		 * \param y la position en y de l'image
		 * \param largeur la largeur de l'image
		 * \param hauteur la hauteur de l'image
		 */
		Image(int nom, int x, int y, int largeur, int hauteur);

		/**
		 * \brief Constructeur
		 *
		 * \param nom le nom de l'image
		 * \param x la position en x de l'image
		 * \param y la position en y de l'image
		 * \param largeur la largeur de l'image
		 * \param hauteur la hauteur de l'image
		 * \param sprite le sprite de l'image
		 */
		Image(int nom, int x, int y, int largeur, int hauteur,
			sf::Sprite sprite);

		/**
		 * \brief Destructeur
		 */
		virtual ~Image();

		/**
		 * \brief Change le sprite de l'image
		 *
		 * \param sprite le nouveau sprite
		 */
		void ecrireSprite(sf::Sprite sprite);

		/**
		 * \brief Récupère le sprite de l'image
		 *
		 * \return le sprite de l'image
		 */
		sf::Sprite& lireSprite();

		// Héritées d'Element
		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
};

#endif /* IMAGE_HPP */
