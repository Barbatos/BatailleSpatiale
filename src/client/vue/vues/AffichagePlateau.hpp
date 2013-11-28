/*
 * AffichagePlateau.hpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGEPLATEAU_HPP
#define AFFICHAGEPLATEAU_HPP

// Includes de la libstd
#include <vector>
#include <memory>

// Includes de nos classes
#include <client/vue/gui/Element.hpp>
#include <client/vue/gui/ElementSouris.hpp>
#include <client/vue/gui/ElementClavier.hpp>
#include "AffichageDetails.hpp"

// Typedefs
typedef std::shared_ptr<AffichageDetails> AffichageDetailsPtr;

/**
 * \brief Affiche le plateau dans son intégralité
 *
 * Gère l'affichage des cases, du vaisseau selectionné, etc
 * Bref, de plus ou moins toute l'interface de la scène jeu
 *
 * \see SceneJeu
 * \see ElementSouris
 */
class AffichagePlateau :
	public Element, public ElementSouris, public ElementClavier
{
	private:
		/**
		 * \brief Représente une case du plateau
		 */
		struct Case
		{
			public:
				/**
				 * \brief La position en x de la case
				 */
				int x;

				/**
				 * \brief La position en y de la case
				 */
				int y;

				/**
				 * \brief La position de la case liée
				 */
				Position position;

				/**
				 * \brief L'image présente sur la case
				 */
				sf::Sprite image;

				/**
				 * \brief L'héxagone de fond de la case
				 */
				sf::CircleShape fond;
		};

		/**
		 * \brief Les cases affichées
		 *
		 * \see AffichageCase
		 */
		std::vector<Case> cases;

		/**
		 * \brief Les détails sur la case actuellement selectionnée
		 *
		 * \see AffichageDetails
		 */
		AffichageDetailsPtr details;

		/**
		 * \brief Taille d'une case
		 */
		int tailleCase;

		/**
		 * \brief La cellule actuellement selectionnée
		 */
		Position selection;

		/**
		 * \brief La cellule actuellement survolée
		 */
		Position survol;

		/**
		 * \brief La vue du plateau
		 */
		sf::View vuePlateau;

		/**
		 * \brief La vue de l'interface
		 */
		sf::View vueInterface;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé un nouvel affichage plateau
		 *
		 * @param nom le nom de l'affichage
		 * @param x la position en x de l'affichage
		 * @param y la position en y de l'affichage
		 * @param largeur la largeur de l'affichage
		 * @param hauteur la hauteur de l'affichage
		 */
		AffichagePlateau(int nom, int x, int y, int largeur, int hauteur);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée d'affichage plateau
		 */
		virtual ~AffichagePlateau();

		/**
		 * \brief Donne la cellule actuellement présente sous la souris
		 *
		 * Prends en paramètre la position actuelle de la souris, et renvoie la position
		 * de la cellule correspondante.
		 *
		 * @param souris la position de la souris
		 * @return la position de la cellule correspondante
		 */
		Position positionCellule(sf::Vector2f souris);

		void dessinerCase(Affichage& affichage, Case c, bool survol,
			bool selectionne);

		void bougerPlateau(float x, float y);

		// Héritées d'ElementSouris
		void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
		void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surMoletteSouris(sf::Event::MouseWheelEvent evenement);

		// Héritées d'ElementClavier
		void surPressionToucheClavier(sf::Event::KeyEvent evenement);
		void surRelachementToucheClavier(sf::Event::KeyEvent evenement);
		void surTexteClavier(sf::Event::TextEvent evenement);

		// Héritées d'Element
		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
};

#endif /* AFFICHAGEPLATEAU_HPP */
