/*
 * Animation.hpp
 *
 * >>>> Ne pas formater svp :( <<<<
 *
 *  Created on: 14 nov. 2013
 *      Author: Thornydre
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "GeneriquesPack.hpp"

/**
 * \brief Représente une animation
 */
class Animation :
	public Element
{
	private:
		/**
		 * \brief Le sprite contenant toutes les images de l'animation
		 */
		sf::Sprite sprite;

		/**
		 * \brief La position de l'image actuellement sélectionnée
		 */
		sf::Vector2u selection;

		/**
		 * \brief Le temps écoulé au total
		 */
		int time;

		/**
		 * \brief Si la méthode de fondu doit être en ajout ou non
		 */
		bool ajout;

		/**
		 * \brief Si l'animation est active ou non
		 */
		bool active;

	public:
		/**
		 * \brief Constructeur
		 *
		 * \param gui le gui contenant l'animation
		 * \param id l'id de l'animation
		 * \param x la position en x de l'animation
		 * \param y la position en y de l'animation
		 * \param largeur la largeur de l'animation
		 * \param hauteur la hauteur de l'animation
		 * \param ajout si l'animation doit être en mode ajout ou non
		 * \param nomImage le nom de l'image à charger
		 */
		Animation(Gui* gui, int id, int x, int y, int largeur, int hauteur,
			bool ajout, std::string nomImage);

		/**
		 * \brief Destructeur
		 */
		virtual ~Animation();

		/**
		 * \brief Change le sprite de l'animation
		 *
		 * \param sprite le nouveau sprite de l'animation
		 */
		void ecrireSprite(sf::Sprite sprite);

		/**
		 * \brief Retourne le sprite de l'animation
		 *
		 * \return le sprite de l'animation
		 */
		sf::Sprite& lireSprite();

		/**
		 * \brief Stoppe l'animation
		 *
		 * Stoppe l'animation et la réinitialise
		 */
		void stop();

		/**
		 * \brief Pause l'animation
		 *
		 * Met en pause l'animation, permettant de la reprendre avec la fonction resumer() plus tard
		 */
		void pause();

		/**
		 * \brief Lance l'animation
		 *
		 * Relance l'animation depuis le début
		 */
		void lancer();

		/**
		 * \brief Résume l'animation
		 *
		 * Relance l'animation à partir de là où elle était avant d'être arrêtée
		 */
		void resumer();

		// Héritées d'Element
		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);

		/**
		 * \class Animation
		 *
		 * Correspond à une suite d'image, changeant toutes les x secondes
		 *
		 * Exemple d'utilisation :
		 *
		 \code
		 // Dans le constructeur d'une scène :
		 // Ajoute une Animation à l'objet 'gui' de type Gui préalablement créé,
		 // avec l'id 1 à la position 0x/5y, faisant 50 par 60 pixels,
		 // à partir de l'image 'animation', préalablement créée

		 new Animation(&gui, 1, 0, 5, 50, 60, animation);

		 // Partout ailleurs :

		 // Objet animation à définir préablement
		 Animation animation;

		 // Lance l'animation (lancée par défaut lors de la construction)
		 animation.lancer();

		 // Met en pause l'animation
		 animation.pause();

		 // Relance l'animation mise en pause
		 animation.resumer();

		 // Stoppe l'animation
		 animation.stop();

		 // Relance l'animation
		 animation.lancer();
		 \endcode
		 *
		 * \see Element
		 */
};

#endif /* ANIMATION_HPP */
