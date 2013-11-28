/*
 * ZoneTexte.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Soinou
 */

#ifndef ZONETEXTE_HPP
#define ZONETEXTE_HPP

// Includes de la libstd
#include <string>

// Includes de la SFML
#include <SFML/Graphics.hpp>

// Includes de nos classes
#include "Element.hpp"
#include "ElementClavier.hpp"
#include "ElementSouris.hpp"
#include "Label.hpp"

/**
 * \brief Représente une zone dans laquelle on peut entrer du texte
 */
class ZoneTexte :
	public Element, public ElementSouris, public ElementClavier
{
	private:
		/**
		 * \brief Le rectangle autour de la zone
		 */
		sf::RectangleShape rectangle;

		/**
		 * \brief Le curseur à la fin du texte
		 */
		sf::RectangleShape curseur;

		/**
		 * \brief Le texte à l'intérieur de la zone
		 */
		Label label;

		/**
		 * \brief Si la zone est survolée
		 */
		bool survole;

		/**
		 * \brief Si la zone est selectionnée
		 */
		bool selectionne;

		/**
		 * \brief Le texte entré dans la zone
		 */
		std::string texte;

		/**
		 * \brief Le texte de remplacement, affiché quand aucun texte n'est entré
		 */
		std::string remplacement;

		/**
		 * \brief Retourne si le caractère unicode donné est autorisé ou non
		 *
		 * \param unicode le caractère à tester
		 * \return true si il est autorisé, false sinon
		 */
		bool estAutorise(int unicode);

	public:
		/**
		 * \brief Constructeur
		 */
		ZoneTexte(int nom, int x, int y, int largeur, int hauteur, std::string remplacement = "");

		/**
		 * \brief Destructeur
		 */
		virtual ~ZoneTexte();

		/**
		 * \brief Retourne le texte entré dans la zone de texte
		 *
		 * \return le texte entré dans la zone
		 */
		std::string lireTexte();

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

		/**
		 * \class ZoneTexte
		 *
		 * Zone de texte pouvant être utilisée pour récupérer une chaîne de caractères de l'utilisateur
		 *
		 * Exemple d'utilisation :
		 *
		 \code

		 // Définition d'une scène
		 class UneScene : public Scene
		 {
		 	 ..
		 	 enum Boutons
		 	 {
		 	 	 Zone
		 	 }
		 	 ZoneScene zone;
		 	 ..
		 }

		 // Constructeur d'une scène
		 UneScene() :
		 	 Scene(),
		 	 zone(Boutons.Zone, 100, 100, 200, 50)
		 {
			 ajouter(zone);
			 enregistrerSouris(zone);
			 enregistrerClavier(zone);
		 }

		 \endcode
		 */
};

#endif /* ZONETEXTE_HPP */
