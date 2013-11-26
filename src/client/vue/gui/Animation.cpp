/*
 * Animation.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#include "Animation.hpp"

#include <client/utile/Utile.hpp>
#include <client/vue/Affichage.hpp>

Animation::Animation(int nom, int x, int y, int largeur, int hauteur, int nbImages, sf::Sprite sprite) :
		Element(nom, x, y, largeur, hauteur),
		sprite(sprite),
		pos(0),
		time(0),
		nbImages(nbImages)
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
	sprite.setTextureRect(sf::IntRect(480, 0, 480, 480));
	sprite.setPosition(zone.left, zone.top);
	Utile::redimensionnerImage(sprite, zone.width, zone.height, false);
}

void Animation::actualiser(__attribute__((unused)) float delta)
{
	time += delta;

	if(time > 1000/24){
		if((pos * 480) < (nbImages-1)*480){
			pos++;
		}
		else{
			pos = 0;
		}

		sprite.setTextureRect(sf::IntRect(pos * 480, 0, 480, 480));

		time = 0;
	}
}

void Animation::afficher(Affichage& affichage)
{
	affichage.draw(sprite, sf::BlendAdd);
}
