/*
 * AffichageDetails.hpp
 *
 *  Created on: 18 oct. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGEDETAILS_HPP
#define AFFICHAGEDETAILS_HPP

// Includes de la libstd
#include <memory>

// Includes de la SFML
#include <SFML/Graphics.hpp>

// Includes de nos classes
#include <client/vue/gui/Element.hpp>
#include <client/vue/gui/Label.hpp>

// Includes des classes moteur
#include <commun/utile/Position.hpp>

/**
 * \brief Affiche les détails de la case selectionnée
 *
 * Donne les détails de la case actuellement selectionnée,
 * qu'elle possède un vaisseau, un batiment, un evenement ou rien du tout
 *
 * \see Element
 */
class AffichageDetails : public Element
{
	private:
		/**
		 * \brief Le fond
		 *
		 * Le fond de l'affichage des détails, simple rectangle avec une bordure
		 */
		sf::RectangleShape fond;

		/**
		 * \brief Texte à afficher
		 *
		 * Le texte donnant les informations sur la case selectionnée
		 *
		 * \see Label
		 */
		Label label;

		/**
		 * \brief La position actuellemment seléctionnée
		 *
		 * La position actuellement choisie par le joueur
		 *
		 * Vaut (-1, -1) si rien n'est selectionné
		 *
		 * \see Position
		 */
		Position position;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance d'affichage détails
		 *
		 * \param nom le nom de l'élément
		 * \param x la position en x de l'élément
		 * \param y la position en y de l'élément
		 * \param largeur la largeur de l'élément
		 * \param hauteur la hauteur de l'élément
		 */
		AffichageDetails(int nom, float x, float y, float largeur,
				float hauteur);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précedemment créée d'affichage détails
		 */
		virtual ~AffichageDetails();

		/**
		 * \brief Retourne si une case est actuellement selectionnée
		 *
		 * @return si une case est selectionnée
		 */
		bool estSelectionne();

		/**
		 * \brief Retourne la position de la case actuellement selectionnée
		 *
		 * @return la position actuellement selectionnée
		 */
		Position lirePosition();

		/**
		 * \brief Selectionne la case donnée
		 *
		 * Surcharge de selectionner(Position position) et de selectionner()
		 *
		 * \param i la position en i de la case
		 * \param j la position en j de la case
		 */
		void selectionner(int i, int j);

		/**
		 * \brief Selectionne la case donnée
		 *
		 * Surcharge de selectionner(int i, int j) et de selectionner()
		 *
		 * \param position la position de la case
		 */
		void selectionner(Position position);

		/**
		 * \brief Selectionne la case par défaut
		 *
		 * Selectionne la case par défaut (-1, -1), c'est à dire aucune case.
		 * En clair, déselectionne l'éventuelle case selectionnée
		 *
		 * Surcharge de selectionner(int i, int j) et de selectionner(Position position)
		 */
		void selectionner();

		// Héritées d'Element
		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
};

#endif /* AFFICHAGEDETAILS_HPP */
