/*
 * ChargementReseau.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef CHARGEMENTRESEAU_HPP
#define CHARGEMENTRESEAU_HPP

#include "ElementPack.hpp"

class ChargementReseau :
	public Element
{
	public:
		ChargementReseau(Gui* gui, int id);
		virtual ~ChargementReseau();

		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
};

#endif /* CHARGEMENTRESEAU_HPP */
