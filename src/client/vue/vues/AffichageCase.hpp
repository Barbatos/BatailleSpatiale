/*
 * AffichageCase.hpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGECASE_HPP
#define AFFICHAGECASE_HPP

// Includes de la libstd
#include <memory>

// Includes de la SFML
#include <SFML/Graphics.hpp>

// Includes de nos classes
#include <client/vue/gui/Element.hpp>
#include <client/vue/gui/ElementSouris.hpp>
#include <commun/utile/Position.hpp>

typedef std::shared_ptr<sf::View> VuePtr;

/**
 * \brief Représente l'affichage d'une case du plateau
 */
class AffichageCase :
	public Element, public ElementSouris
{
	private:
		/**
		 * \brief L'image affichée sur la case
		 */
		sf::Sprite image;

		/**
		 * \brief Le fond de la case
		 */
		sf::CircleShape fond;

		/**
		 * \brief La position associée à la case
		 */
		Position position;

		/**
		 * \brief La vue qui contient la case
		 */
		VuePtr vuePlateau;

		/**
		 * \brief Si la case est survolée
		 */
		bool survole;

		/**
		 * \brief Si la case est selectionnée
		 */
		bool selectionne;

	public:
		/**
		 * \brief Constructeur
		 */
		AffichageCase(int nom, float x, float y, float taille,
			Position position, sf::View* vuePlateau);

		/**
		 * \brief Destructeur
		 */
		virtual ~AffichageCase();

		/**
		 * \brief Retourne si la case contient le point donné
		 *
		 * @param point le point à tester
		 * @return true si le point se trouve dans la case, false sinon
		 */
		bool contient(sf::Vector2f point);

		// Héritées d'Element
		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);

		// Héritées d'ElementSouris
		void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
		void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surMoletteSouris(sf::Event::MouseWheelEvent evenement);

};

#endif /* AFFICHAGECASE_HPP */
