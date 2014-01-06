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

// Includes du pack element
#include "GeneriquesPack.hpp"
#include "Label.hpp"

/**
 * \brief Représente une zone dans laquelle on peut entrer du texte
 */
class ZoneTexte :
	public Element, public ObservateurSouris, public ObservateurClavier
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
		 * \brief Si la zone est selectionnée
		 */
		bool selectionne;

		/**
		 * \brief Le texte entré dans la zone
		 */
		std::string texte;

		/**
		 * \brief Le texte affiché lorsque la zone de texte est vide
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
		ZoneTexte(Gui* gui, int id, int x, int y, int largeur, int hauteur,
			std::string remplacement = "");

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
		void actualiser(float delta);
		void afficher(sf::RenderWindow& affichage);
		bool contient(sf::Vector2i position);

		// Héritées d'ElementSouris
		void clicSouris();
		void pressionSouris(sf::Mouse::Button bouton);
		void relachementSouris(sf::Mouse::Button bouton);
		void entreeSouris(sf::Vector2f position);
		void sortieSouris(sf::Vector2f position);
		void moletteSouris(int delta);

		// Héritées d'ElementClavier
		void pressionTouche(sf::Keyboard::Key touche);
		void relachementTouche(sf::Keyboard::Key touche);
		void entreeTexte(sf::Uint32 texte);

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
		 enum Elements
		 {
		 Zone
		 }
		 ZoneScene zone;
		 ..
		 }

		 // Constructeur d'une scène
		 UneScene() :
		 Scene(),
		 zone(Boutons.Zone, 100, 100, 200, 50, "Une zone de texte")
		 {
		 ajouter(zone);
		 enregistrerSouris(zone);
		 enregistrerClavier(zone);
		 }

		 \endcode
		 */
};

#endif /* ZONETEXTE_HPP */
