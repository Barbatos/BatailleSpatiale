/*
 * ZoneTexte.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Soinou
 */

#ifndef ZONETEXTE_HPP
#define ZONETEXTE_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "Element.hpp"
#include "ElementClavier.hpp"
#include "ElementSouris.hpp"

#include "Label.hpp"

/**
 * \brief Représente une zone dans laquelle on peut entrer du texte
 */
class ZoneTexte : public Element, public ElementSouris, public ElementClavier
{
	private:
		sf::RectangleShape rectangle;
		Label label;

		bool survole;
		bool selectionne;

		std::string texte;

	public:
		/**
		 * \brief Constructeur
		 */
		ZoneTexte(int nom, int x, int y, int largeur, int hauteur);

		/**
		 * \brief Destructeur
		 */
		virtual ~ZoneTexte();

		// Héritées d'Element
		void initialiser(void);
		void actualiser(float delta);
		void afficher(Affichage& affichage);

		// Héritées d'ElementSouris
		void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
		void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surMoletteSouris(sf::Event::MouseWheelEvent evenement);

		// Héritées d'ElementClavier
		void surPressionToucheClavier(sf::Event::KeyEvent evenement);
		void surRelachementToucheClavier(sf::Event::KeyEvent evenement);
		void surTexteClavier(sf::Event::TextEvent evenement);
};

#endif /* ZONETEXTE_HPP */
