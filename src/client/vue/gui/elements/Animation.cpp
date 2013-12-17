/*
 * Animation.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#include "Animation.hpp"

<<<<<<< HEAD:src/client/vue/gui/elements/Animation.cpp
Animation::Animation(Gui* gui, int id, int x, int y, int largeur, int hauteur,
	bool add, sf::Sprite sprite) :
		Element(gui, id),
		sprite(sprite),
		posx(0),
		posy(0),
		time(0),
		add(add)
=======
#include <iostream>

#include <client/utile/Utile.hpp>
#include <client/vue/Affichage.hpp>

Animation::Animation(int nom, unsigned int x, unsigned int y, int largeur, int hauteur, bool add, sf::Sprite sprite) :
	Element(nom, x, y, largeur, hauteur),
	sprite(sprite),
	posx(0),
	posy(0),
	time(0),
	add(add),
	actualisation(true)
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d:src/client/vue/gui/Animation.cpp
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	sprite.setTextureRect(sf::IntRect(0, 0, 480, 480));
	sprite.setPosition(lirePosition().x, lirePosition().y);
	Utile::redimensionnerImage(sprite, lireTaille().x, lireTaille().y, false);
}

Animation::~Animation()
{
}

void Animation::ecrireSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

sf::Sprite& Animation::lireSprite()
{
	return sprite;
}

void Animation::actualiser(float delta)
{
	time += delta;

	if (time > 1000 / 24)
	{
		if(actualisation)
		{
			if ((posx * 480) < (sprite.getTexture()->getSize().x - 480))
			{
				posx++;
			}
			else
			{
				if ((posy * 480) < (sprite.getTexture()->getSize().y - 480))
				{
					posy++;
				}
				else
				{
					posy = 0;
				}
				posx = 0;
			}
		}

		sprite.setTextureRect(sf::IntRect(posx * 480, posy * 480, 480, 480));

		time = 0;
	}
}

<<<<<<< HEAD:src/client/vue/gui/elements/Animation.cpp
void Animation::afficher(sf::RenderWindow& affichage)
=======
void Animation::stop()
{
	actualisation = false;
}

void Animation::start()
{
	actualisation = true;
}

void Animation::afficher(Affichage& affichage)
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d:src/client/vue/gui/Animation.cpp
{
	if (add)
	{
		affichage.draw(sprite, sf::BlendAdd);
	}
	else
	{
		affichage.draw(sprite);
	}
}

bool Animation::contient(sf::Vector2i position)
{
	return sprite.getGlobalBounds().contains(position.x, position.y);
}
