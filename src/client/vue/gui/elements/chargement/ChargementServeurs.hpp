/*
 * ChargementServeurs.hpp
 *
 *  Created on: Feb 11, 2014
 *      Author: Soinou
 */

#ifndef CHARGEMENTSERVEURS_HPP
#define CHARGEMENTSERVEURS_HPP

class ChargementServeurs: public Element {
private:
	Label texte;
	Animation image;

public:
	ChargementServeurs(Gui* gui, int id, int x, int y, int largeur,
			int hauteur);
	virtual ~ChargementServeurs();

	void actualiser(float delta);
	void afficher();
	bool contient(sf::Vector2i position);
};

#endif /* CHARGEMENTSERVEURS_HPP */
