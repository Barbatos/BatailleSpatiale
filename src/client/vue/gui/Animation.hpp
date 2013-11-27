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
		int posx;
		int posy;
		int time;
		int add;

	public:
		Animation(int nom, int x, int y, int largeur, int hauteur, int add, sf::Sprite sprite);

		virtual ~Animation();

		void ecrireSprite(sf::Sprite sprite);

		sf::Sprite& lireSprite();

		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
};

#endif /* ANIMATION_HPP_ */
