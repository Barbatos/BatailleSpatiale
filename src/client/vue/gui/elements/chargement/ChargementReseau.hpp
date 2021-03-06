/*
 * ChargementReseau.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef CHARGEMENTRESEAU_HPP
#define CHARGEMENTRESEAU_HPP

#include "ChargementPack.hpp"

#include <client/vue/gui/elements/generiques/Animation.hpp>
#include <client/vue/gui/elements/generiques/Label.hpp>

class ChargementReseau: public Element {
private:
	Label texte;
	Animation image;
	bool reseauActif;

public:
	ChargementReseau(Gui* gui, int id, int x, int y, int largeur, int hauteur);
	virtual ~ChargementReseau();

	void actualiser(float delta);
	void afficher();
	bool contient(sf::Vector2i position);
	void setReseauActif(bool _actif);
};

#endif /* CHARGEMENTRESEAU_HPP */
