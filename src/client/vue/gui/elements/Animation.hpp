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
<<<<<<< HEAD:src/client/vue/gui/elements/Animation.hpp
		Animation(Gui* gui, int id, int x, int y, int largeur, int hauteur,
			bool add, sf::Sprite sprite);
=======
		Animation(int nom, unsigned int x, unsigned int y, int largeur, int hauteur, bool add, sf::Sprite sprite);
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d:src/client/vue/gui/Animation.hpp

		virtual ~Animation();

		void ecrireSprite(sf::Sprite sprite);

		sf::Sprite& lireSprite();

		void actualiser(float delta);
<<<<<<< HEAD:src/client/vue/gui/elements/Animation.hpp
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
=======
		void stop();
		void start();
		void afficher(Affichage& affichage);
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d:src/client/vue/gui/Animation.hpp
};

#endif /* ANIMATION_HPP_ */
