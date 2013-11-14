/*
 * ElementClavier.hpp
 *
 *  Created on: 19 oct. 2013
 *      Author: Soinou
 */

#ifndef ELEMENTCLAVIER_HPP
#define ELEMENTCLAVIER_HPP

// Includes de la SFML
#include <SFML/Window.hpp>

class ElementClavier
{
	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance d'ElementClavier
		 */
		ElementClavier();

		/**
		 * \brief Destructeur
		 *
		 * Détruit une instance précédemment créé d'ElementClavier
		 */
		virtual ~ElementClavier();

		/**
		 * \brief Fonction de "Callback" appelée lors de la pression d'une touche du clavier
		 *
		 * Fonction appelée lorsqu'une touche du clavier est appuyée
		 *
		 * \param evenement l'évènement généré
		 */
		virtual void surPressionToucheClavier(
				sf::Event::KeyEvent evenement) = 0;

		/**
		 * \brief Fonction de "Callback" appelée lors de la pression d'une touche du clavier
		 *
		 * Fonction appelée lorsqu'une touche du clavier est relâchée
		 *
		 * \param evenement
		 */
		virtual void surRelachementToucheClavier(
				sf::Event::KeyEvent evenement) = 0;

		/**
		 * \brief Fonction de "Callback" appelée lors de la pression d'une touche du clavier
		 *
		 * Fonction appelée lorsque du texte est entré via le clavier.
		 * Différent de surPressionToucheClavier() puisque le texte est au format unicode
		 *
		 * \param evenement
		 */
		virtual void surTexteClavier(sf::Event::TextEvent evenement) = 0;

		/**
		 * \class ElementClavier
		 *
		 * \brief Interface définissant un élément écoutant les évènements liés au clavier.
		 *
		 * Pour l'utiliser il faut créer un nouvel objet en héritant, et implémenter les fonctions
		 * de Callback appelées lorsqu'un évènement se passe.
		 *
		 * Exemple d'utilisation :
		 *
		 \code
		 class ObjetClavier : public ElementClavier
		 {
			 public:
				 ObjetClavier();
				 ~ObjetClavier() { }

				 void surPressionToucheClavier(sf::Event::KeyEvent evenement);
				 void surRelachementToucheClavier(sf::Event::KeyEvent evenement);
				 void surTexteClavier(sf::Event::TextEvent evenement);
		 }

		 ObjetClavier::ObjetClavier()
		 {
		 }

		 void ObjetClavier::surPressionToucheClavier(sf::Event::KeyEvent evenement)
		 {
		 	 // Une touche du clavier a été appuyée !
		 }

		 void ObjetClavier::surRelachementToucheClavier(sf::Event::KeyEvent evenement)
		 {
			 // Une touche du clavier a été relâchée !
			 // On peut donc supposer qu'elle a été appuyée avant.
		 }

		 void ObjetClavier::surTexteClavier(sf::Event::TextEvent evenement)
		 {
			 // Du texte a été entré. surPressionToucheClavier() a du recevoir l'évènement
			 // également, mais dans cette fonction là les caractères sont reçus au format unicode
		 }
		 \endcode
		 *
		 * \see ElementSouris
		 */
};

#endif /* ELEMENTCLAVIER_HPP */
