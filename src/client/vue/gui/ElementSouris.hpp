/*
 * ElementSouris.hpp
 *
 *  Created on: 19 oct. 2013
 *      Author: Soinou
 */

#ifndef ELEMENTSOURIS_HPP
#define ELEMENTSOURIS_HPP

// Includes de la SFML
#include <SFML/Window.hpp>

class ElementSouris
{
	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance d'ElementSouris
		 */
		ElementSouris();

		/**
		 * \brief Destructeur
		 *
		 * Détruit une instance précédemment créée d'ElementSouris
		 */
		virtual ~ElementSouris();

		/**
		 * \brief Fonction de "Callback" appelée lors du mouvement de la souris
		 *
		 * Fonction appelée lorsque la souris est déplacée
		 *
		 * \param evenement l'évènement généré
		 */
		virtual void surMouvementSouris(
				sf::Event::MouseMoveEvent evenement) = 0;

		/**
		 * \brief Fonction de "Callback" appelée lors de la pression d'un des boutons de la souris
		 *
		 * Fonction appelée lorsqu'un des boutons de la souris est appuyé
		 *
		 * \param evenement l'évènement généré
		 */
		virtual void surPressionBoutonSouris(
				sf::Event::MouseButtonEvent evenement) = 0;

		/**
		 * \brief Fonction de "Callback" appelée lors du relâchement d'un des boutons de la souris
		 *
		 * Fonction appelée lorsqu'un des boutons de la souris est relâché
		 *
		 * \param evenement l'évènement généré
		 */
		virtual void surRelachementBoutonSouris(
				sf::Event::MouseButtonEvent evenement) = 0;

		/**
		 * \brief Fonction de "Callback" appelée lors de l'utilisation de la molette de la souris
		 *
		 * Fonction appelée lorsque la molette de la souris est utilisée
		 *
		 * \param evenement
		 */
		virtual void surMoletteSouris(sf::Event::MouseWheelEvent evenement) = 0;

		/**
		 * \class ElementSouris
		 *
		 * \brief Interface définissant un élément écoutant les évènements liés à la souris.
		 *
		 * Pour l'utiliser il faut créer un nouvel objet en héritant, et implémenter les fonctions
		 * de Callback appelées lorsqu'un évènement se passe.
		 *
		 * Exemple d'utilisation :
		 *
		 \code
		 class ObjetSouris : public ElementSouris
		 {
			 public:
				 ObjetSouris();
				 ~ObjetSouris() { }

				 void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
				 void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
				 void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
				 void surMoletteSouris(sf::Event::MouseWheelEvent evenement);
		 }

		 ObjetSouris::ObjetSouris() : ElementSouris()
		 {
		 }

		 void ObjetSouris::surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement)
		 {
		 	 // Un bouton de la souris a été appuyé!
		 }

		 void ObjetSouris::surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement)
		 {
		 	 // Un bouton de la souris a été relâché !
		 	 // On peut donc supposer qu'il a été appuyé avant
		 }

		 void ObjetSouris::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
		 {
		 	 // La souris a été déplacée !
		 }

		 void ObjetSouris::surMoletteSouris(sf::Event::MouseWheelEvent evenement)
		 {
		 	 // La molette de la souris a été utilisée !
		 }
		 \endcode
		 *
		 * \see ElementSouris
		 */
};

#endif /* ELEMENTSOURIS_HPP */
