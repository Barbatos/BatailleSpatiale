/*
 * Animation.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#include "Animation.hpp"

Animation::Animation(Gui* gui, int id, int x, int y, int largeur, int hauteur,
                     bool add, bool cycle, std::string nomImage) :
	Element(gui, id),
	sprite(gui->lireScene()->lireJeu().lireRessources().lireImage(
	           nomImage)),
	selection(),
	time(0),
	ajout(add),
	active(true),
	cyclique(cycle) {
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	sprite.setTextureRect(sf::IntRect(0, 0, 480, 480));
	sprite.setPosition(lirePosition().x, lirePosition().y);
	Utile::redimensionnerImage(sprite, lireTaille().x, lireTaille().y, false);
}

Animation::~Animation() {
}

void Animation::ecrireSprite(sf::Sprite sprite) {
	this->sprite = sprite;
}

sf::Sprite& Animation::lireSprite() {
	return sprite;
}

void Animation::actualiser(float delta) {
	time += delta;

	if (time > 1000 / 24) {
		if (active) {
			if ((selection.x * 480) < (sprite.getTexture()->getSize().x - 480)) {
				selection.x++;
			} else {
				if ((selection.y * 480) < (sprite.getTexture()->getSize().y - 480)) {
					selection.y++;
				} else {
					selection.y = 0;
				}
				selection.x = 0;
			}

			if(!cyclique){
				if((selection.x + 1  == sprite.getTexture()->getSize().x / 480) and (selection.y + 1  == sprite.getTexture()->getSize().y / 480)){
					active = false;
				}
			}
		}

		sprite.setTextureRect(
		    sf::IntRect(selection.x * 480, selection.y * 480, 480, 480));

		time = 0;
	}
}

void Animation::stop() {
	selection.x = 0;
	selection.y = 0;

	pause();
}

void Animation::pause() {
	active = false;
}

void Animation::lancer() {
	selection.x = 0;
	selection.y = 0;

	resumer();
}

void Animation::resumer() {
	active = true;
}

void Animation::afficher(sf::RenderWindow& affichage) {
	if (ajout) {
		affichage.draw(sprite, sf::BlendAdd);
	} else {
		affichage.draw(sprite);
	}
}

bool Animation::contient(sf::Vector2i position) {
	return sprite.getGlobalBounds().contains(position.x, position.y);
}
