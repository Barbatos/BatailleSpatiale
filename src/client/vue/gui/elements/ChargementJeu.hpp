/*
 * ChargementJeu.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef CHARGEMENTRESEAU_HPP
#define CHARGEMENTJEU_HPP

#include "ElementPack.hpp"

class ChargementJeu :
	public Element
{
	public:
		ChargementJeu(Gui* gui, int id);
		virtual ~ChargementJeu();

		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
};

#endif /* CHARGEMENTJEU_HPP */
