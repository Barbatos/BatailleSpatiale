/*
 * Animation.hpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "ElementPack.hpp"

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
		Animation(Gui* gui, int id, int x, int y, int largeur, int hauteur,
			bool add, sf::Sprite sprite);

		virtual ~Animation();

		void ecrireSprite(sf::Sprite sprite);

		sf::Sprite& lireSprite();

		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
		void stop();
		void start();
};

#endif /* ANIMATION_HPP */
