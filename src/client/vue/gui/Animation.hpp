/*
 * Animation.hpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "Element.hpp"

class Animation :
		public Element
{
	private:
		sf::Sprite sprite;
		int pos;
		int time;
		int nbImages;

	public:
		Animation(int nom, int x, int y, int largeur, int hauteur, int nbImages, sf::Sprite sprite);

		virtual ~Animation();

		void ecrireSprite(sf::Sprite sprite);

		sf::Sprite& lireSprite();

		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
};

#endif /* ANIMATION_HPP_ */
