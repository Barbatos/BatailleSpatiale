/*
 * BoutonDeplacementCarte.hpp
 *
 *  Created on: 5 déc. 2013
 *      Author: Thornydre
 */

#ifndef BOUTONDEPLACEMENTCARTE_HPP_
#define BOUTONDEPLACEMENTCARTE_HPP_

// Includes de la SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Includes de nos classes
#include "Element.hpp"
#include "ElementSouris.hpp"
#include "Label.hpp"

class Affichage;

class BoutonDeplacementCarte : public Element, public ElementSouris
{
	private:
		bool survole;
		sf::RectangleShape normal;
		sf::RectangleShape survol;

	public:
		BoutonDeplacementCarte(int nom, float x, float y, float largeur, float hauteur);
		virtual ~BoutonDeplacementCarte();

		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
		void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
		void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surMoletteSouris(sf::Event::MouseWheelEvent evenement);
	};

#endif /* BOUTONDEPLACEMENTCARTE_HPP_ */
