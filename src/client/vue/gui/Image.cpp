/*
 * Image.cpp
 *
 *  Created on: 12 nov. 2013
 *      Author: Soinou
 */

#include "Image.hpp"

#include <client/utile/Utile.hpp>
#include <client/vue/Affichage.hpp>

Image::Image(int nom, int x, int y, int largeur, int hauteur) :
		Element(nom, x, y, largeur, hauteur),
		sprite()
{
}

Image::Image(int nom, int x, int y, int largeur, int hauteur, sf::Sprite sprite) :
		Element(nom, x, y, largeur, hauteur),
		sprite(sprite)
{
}

Image::~Image()
{
}

void Image::ecrireSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

sf::Sprite& Image::lireSprite()
{
	return sprite;
}

void Image::initialiser()
{
	sprite.setPosition(zone.left, zone.top);
	Utile::redimensionnerImage(sprite, zone.width, zone.height, false);
}
void Image::actualiser(__attribute__((unused)) float delta)
{

}

void Image::afficher(Affichage& affichage)
{
	affichage.draw(sprite);
}
