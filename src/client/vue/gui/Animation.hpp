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
		unsigned int posx;
		unsigned int posy;
		int time;
		bool add;
		bool actualisation;

	public:
		Animation(int nom, unsigned int x, unsigned int y, int largeur, int hauteur, bool add, sf::Sprite sprite);

		virtual ~Animation();

		void ecrireSprite(sf::Sprite sprite);

		sf::Sprite& lireSprite();

		void initialiser();
		void actualiser(float delta);
		void stop();
		void start();
		void afficher(Affichage& affichage);
};

#endif /* ANIMATION_HPP_ */
