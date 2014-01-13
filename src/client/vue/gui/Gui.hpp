/*
 * Gui.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef GUI_HPP
#define GUI_HPP

// Includes de la stdlib
#include <queue>
#include <memory>

// Includes de la SFML
#include <SFML/Window/Event.hpp>

// Includes de nos classes
#include "Element.hpp"
#include "evenements/ObservateurSouris.hpp"
#include "evenements/ObservateurClavier.hpp"
class Scene;

/**
 * \brief Représente une interface, contenant des éléments graphiques
 *
 * Contient tout les élements affichés à l'écran, et intéragit avec eux
 *
 * TODO: Documenter le gui
 */
class Gui
{
	private:
		/**
		 *
		 */
		std::vector<Element::Ptr> elements;

		/**
		 *
		 */
		std::queue<int> messages;

		/**
		 *
		 */
		sf::Clock horloge;

		/**
		 *
		 */
		sf::RenderWindow* fenetre;

		/**
		 *
		 */
		Scene* scene;

	public:
		/**
		 *
		 */
		typedef std::shared_ptr<Gui> Ptr;

		/**
		 *
		 */
		Gui(sf::RenderWindow* fenetre, Scene* scene);

		/**
		 *
		 */
		virtual ~Gui();

		/**
		 *
		 * @return
		 */
		Scene* lireScene();

		/**
		 *
		 * @param element
		 */
		void ajouter(Element::Ptr element);

		/**
		 *
		 * @param element
		 */
		void ajouter(Element* element);

		/**
		 *
		 * @param id
		 */
		void ajouterMessage(int id);

		/**
		 *
		 * @param evenement
		 */
		void traiter(sf::Event evenement);

		void actualiser();

		void afficher();

		/**
		 *
		 * @param id
		 * @return
		 */
		bool obtenirMessage(int* id);
};

#endif /* GUI_HPP */
