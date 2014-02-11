/*
 * Image.cpp
 *
 *  Created on: 12 nov. 2013
 *      Author: Soinou
 */

#include "Image.hpp"

Image::Image(Gui* gui, int id, int x, int y, int largeur, int hauteur) :
	Element(gui, id),
	sprite() {
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	sprite.setPosition(lirePosition().x, lirePosition().y);
	Utile::redimensionnerImage(sprite, lireTaille().x, lireTaille().y, false);
}

Image::Image(Gui* gui, int id, int x, int y, int largeur, int hauteur,
             sf::Sprite sprite) :
	Element(gui, id),
	sprite(sprite) {
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	sprite.setPosition(lirePosition().x, lirePosition().y);
	Utile::redimensionnerImage(sprite, lireTaille().x, lireTaille().y, false);
}

Image::~Image() {
}

void Image::ecrireSprite(sf::Sprite sprite) {
	this->sprite = sprite;
}

sf::Sprite& Image::lireSprite() {
	return sprite;
}

void Image::actualiser(float) {

}

void Image::afficher() {
	affichage.draw(sprite);
}

bool Image::contient(sf::Vector2i position) {
	return sprite.getGlobalBounds().contains(position.x, position.y);
}
