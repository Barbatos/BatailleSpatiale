/*
 * ChargementJeu.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef CHARGEMENTRESEAU_HPP
#define CHARGEMENTJEU_HPP

#include "ChargementPack.hpp"

#include <client/vue/gui/elements/generiques/Animation.hpp>
#include <client/vue/gui/elements/generiques/Label.hpp>

class ChargementJeu :
	public Element
{
	private:
		Label texte;
		Animation image;

	public:
		ChargementJeu(Gui* gui, int id, int x, int y, int largeur, int hauteur);
		virtual ~ChargementJeu();

		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);
};

#endif /* CHARGEMENTJEU_HPP */
