/*
 * Animation.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#include "Animation.hpp"

#include <iostream>

#include <client/utile/Utile.hpp>
#include <client/vue/Affichage.hpp>

Animation::Animation(int nom, int x, int y, int largeur, int hauteur, bool add,
	sf::Sprite sprite) :
		Element(nom, x, y, largeur, hauteur),
		sprite(sprite),
		posx(0),
		posy(0),
		time(0),
		add(add)
{
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

void Animation::initialiser()
{
	sprite.setTextureRect(sf::IntRect(0, 0, 480, 480));
	sprite.setPosition(zone.left, zone.top);
	Utile::redimensionnerImage(sprite, zone.width, zone.height, false);
}

void Animation::actualiser(float delta)
{
	time += delta;

	if (time > 1000 / 24)
	{
		if ((posx * 480) < sprite.getTexture()->getSize().x - 480)
		{
			posx++;
		}
		else
		{
			if ((posy * 480) < sprite.getTexture()->getSize().y - 480)
			{
				posy++;
			}
			else
			{
				posy = 0;
			}
			posx = 0;
		}

		sprite.setTextureRect(sf::IntRect(posx * 480, posy * 480, 480, 480));

		time = 0;
	}
}

void Animation::afficher(Affichage& affichage)
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
