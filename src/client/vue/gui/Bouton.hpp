/*
 * Bouton.hpp
 *
 *  Created on: 5 oct. 2013
 *      Author: Tendry
 */

#ifndef BOUTON_HPP
#define BOUTON_HPP

// Includes de la SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Includes de nos classes
#include "Element.hpp"
#include "ElementSouris.hpp"
#include "Label.hpp"

// Pré-déclarations
class Affichage;

/**
 * \brief Simple bouton générique
 */
class Bouton : public Element, public ElementSouris
{
	private:
		/**
		 * \brief Un label
		 *
		 * Le label présent sur le bouton
		 */
		Label label;

		/**
		 * \brief L'image normale du bouton
		 *
		 * L'image du bouton lorsqu'il ne se passe rien
		 */
		sf::Sprite normal;

		/**
		 * \brief L'image du bouton au survol
		 *
		 * L'image du bouton lorsqu'il est survolé
		 */
		sf::Sprite survol;

		/**
		 * \brief L'image du bouton à l'appui
		 *
		 * L'image du bouton lorsqu'il est appuyé
		 */
		sf::Sprite appui;

		/**
		 * \brief Si le bouton est survolé ou non.
		 */
		bool survole;

		/**
		 * \brief Si le vouton est appuyé ou non.
		 */
		bool appuye;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé un nouveau bouton avec les paramètres donnés
		 *
		 * \param nom le nom du bouton
		 * \param texte le texte du bouton
		 * \param x sa position en x
		 * \param y sa position en y
		 * \param largeur sa largeur
		 * \param hauteur sa hauteur
		 */
		Bouton(int nom, std::string texte, float x, float y, float largeur, float hauteur);

		/**
		 * \brief Destructeur
		 *
		 * Détruit un bouton précédemment créé
		 */
		virtual ~Bouton();

		// Héritées de ElementSouris
		void initialiser();
		void actualiser(float delta);
		void afficher(Affichage& affichage);
		void surMouvementSouris(sf::Event::MouseMoveEvent evenement);
		void surPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);
		void surMoletteSouris(sf::Event::MouseWheelEvent evenement);

		/**
		 * \class Bouton
		 *
		 * Bouton simple, qu'on peut cliquer pour effectuer une action
		 *
		 * Exemple d'utilisation :
		 *
		 \code
		 // Dans le constructeur d'une scène :
		 // Création d'un bouton avec l'id 0, possédant le texte "Je suis un bouton", en position
		 // 50x/50y, faisant 200 par 20 pixels
		 Bouton* btnbouton1 = new Bouton(0, "Je suis un bouton !", 50, 50, 200, 20);

		 // Ajoute le bouton à la scène
		 ajouter(btnbouton1);

		 // Demande au bouton d'écouter les évènements qui se passent dans la scène
		 enregistrerSouris(btnbouton1);


		 // Dans la fonction surMessage() de la même scène :
		 switch(message)
		 {
		 	 case Clic:
		 	 	 switch(nom)
		 	 	 {
		 	 	 	 case 0:
		 	 	 	 	 // La souris a cliqué sur notre bouton
		 	 	 	 	 faireQuelqueChose();
		 	 	 	 	 break;
		 	 	 	 default:
		 	 	 	 	 break;
		 	 	 }
		 	 	 break;
		 	 case Entre:
		 	 	 switch(nom)
		 	 	 {
		 	 	 	 case 0:
		 	 	 	 	 // La souris est entrée dans notre bouton
		 	 	 	 	 faireAutreChose();
		 	 	 	 	 break;
		 	 	 	 default:
		 	 	 	 	 break;
		 	 	 }
		 	 	 break;
		 	 case Sort:
		 	 	 switch(nom)
		 	 	 {
		 	 	 	 case 0:
		 	 	 	 	 // La souris est sortie de notre bouton !
		 	 	 	 	 faireEncoreAutreChose();
		 	 	 	 	 break;
		 	 	 	 default:
		 	 	 	 	 break;
		 	 	 }
		 	 	 break;
		 	 default:
		 	 	 break;
		 }
		 \endcode
		 *
		 * \see Scene
		 */
};

#endif /* BOUTON_HPP */
