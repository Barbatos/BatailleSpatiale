/*
 * BoutonDeplacementCarte.hpp
 *
 *  Created on: 5 d�c. 2013
 *      Author: Thornydre
 */

#ifndef BOUTONDEPLACEMENTCARTE_HPP_
#define BOUTONDEPLACEMENTCARTE_HPP_

// Includes de la SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Includes de nos classes
#include "ElementPack.hpp"
#include "Label.hpp"

class Affichage;

class BoutonDeplacementCarte :
	public Element, public ObservateurSouris
{
	private:
		sf::RectangleShape normal;
		sf::RectangleShape survol;

	public:
		BoutonDeplacementCarte(Gui* gui, int id, float x, float y, float largeur,
			float hauteur);
		virtual ~BoutonDeplacementCarte();

		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);

		void clicSouris();
		void pressionSouris(sf::Mouse::Button bouton);
		void relachementSouris(sf::Mouse::Button bouton);
		void entreeSouris(sf::Vector2f position);
		void sortieSouris(sf::Vector2f position);
		void moletteSouris(int delta);
};

#endif /* BOUTONDEPLACEMENTCARTE_HPP */
