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
#include "AffichageCase.hpp"

// Typedefs
typedef std::shared_ptr<AffichageDetails> AffichageDetailsPtr;
typedef std::unique_ptr<AffichageCase> AffichageCasePtr;
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
		 * \brief Les cases affichées
		 *
		 * \see AffichageCase
		 */
		std::vector<AffichageCasePtr> cases;

		/**
		 * \brief Les détails sur la case actuellement selectionnée
		 *
		 * \see AffichageDetails
		 */
		AffichageDetailsPtr details;

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
		 * \brief Déplace la vue plateau
		 *
		 * @param x nombre de pixels à déplacer en x
		 * @param y nombre de pixels à déplacer en y
		 */
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
