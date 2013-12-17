/*
 * Element.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

// Includes de la stdlib
#include <memory>

// Includes de la SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Includes de nos classes
class Gui;
#include "evenements/ObservateurSouris.hpp"
#include "evenements/ObservateurClavier.hpp"

class Element
{
	private:
		/////////////////////////////////////////
		///	General
		/////////////////////////////////////////

		/**
		 * \brief L'ID de l'élement
		 */
		int id;

		/**
		 * \brief Le gui contenant l'élement
		 *
		 * \see Gui
		 */
		Gui* gui;

		/**
		 * \brief La position de l'élement
		 */
		sf::Vector2f position;

		/**
		 * \brief La taille de l'élement
		 */
		sf::Vector2f taille;

		/////////////////////////////////////////
		///	Observateurs
		/////////////////////////////////////////

		/**
		 * \brief Si l'élement observe les évènements de la souris
		 */
		bool souris;

		/**
		 * \brief Si l'élement observe les évènements du clavier
		 */
		bool clavier;

		/**
		 * \brief Observateur de la souris
		 *
		 * \see ObservateurSouris
		 */
		ObservateurSouris::Ptr observateurSouris;

		/**
		 * \brief Observateur du clavier
		 *
		 * \see ObservateurClavier
		 */
		ObservateurClavier::Ptr observateurClavier;

	protected:
		/////////////////////////////////////////
		///	Divers
		/////////////////////////////////////////

		/**
		 * \brief Si l'élement est survolé
		 */
		bool survol;

		/**
		 * \brief Si l'élement est appuyé
		 */
		bool appui;

	public:
		/////////////////////////////////////////
		///	Typedef
		/////////////////////////////////////////
		typedef std::shared_ptr<Element> Ptr;

		/////////////////////////////////////////
		///	Constructeurs / Destructeurs
		/////////////////////////////////////////

		/**
		 * \brief Constructeur
		 *
		 * Appelle Element(Gui::Ptr, int) avec le Gui* transformé en Gui::Ptr
		 *
		 * @param gui le gui contenant l'élement
		 * @param id l'id de l'élement
		 */
		Element(Gui* gui, int id);

		/**
		 * \brief Destructeur
		 */
		virtual ~Element();

		/////////////////////////////////////////
		///	Methodes Observateurs
		/////////////////////////////////////////

		/**
		 *
		 * @return
		 */
		ObservateurSouris::Ptr lireSouris();
		/**
		 *
		 * @return
		 */
		ObservateurClavier::Ptr lireClavier();

		/**
		 *
		 * @param observateur
		 */
		void enregistrerSouris(ObservateurSouris::Ptr observateur);
		/**
		 *
		 * @param observateur
		 */
		void enregistrerClavier(ObservateurClavier::Ptr observateur);

		/**
		 *
		 * @return
		 */
		bool observeSouris();
		/**
		 *
		 * @return
		 */
		bool observeClavier();

		/////////////////////////////////////////
		///	Methodes générales
		/////////////////////////////////////////

		/**
		 *
		 * @return
		 */
		int lireId();

		/**
		 *
		 * \return
		 */
		Gui* lireGui();

		/**
		 *
		 * @param id
		 */
		void ecrireId(int id);

		/**
		 *
		 * @param gui
		 */
		void ecrireGui(Gui* gui);

		/**
		 *
		 * @return
		 */
		sf::Vector2f lireTaille();

		/**
		 *
		 * @return
		 */
		sf::Vector2f lirePosition();

		/**
		 *
		 * @param taille
		 */
		void ecrireTaille(sf::Vector2f taille);
		/**
		 *
		 * @param largeur
		 * @param hauteur
		 */
		void ecrireTaille(float largeur, float hauteur);

		/**
		 *
		 * @param position
		 */
		void ecrirePosition(sf::Vector2f position);
		/**
		 *
		 * @param x
		 * @param y
		 */
		void ecrirePosition(float x, float y);

		/**
		 *
		 * @param zone
		 */
		void ecrireZone(sf::FloatRect zone);

		/////////////////////////////////////////
		///	Methodes diverses
		/////////////////////////////////////////

		/**
		 *
		 * @param survol
		 */
		void ecrireSurvol(bool survol);
		/**
		 *
		 * @param appui
		 */
		void ecrireAppui(bool appui);

		/**
		 *
		 * @return
		 */
		bool lireSurvol();
		/**
		 *
		 * @return
		 */
		bool lireAppui();

		/**
		 *
		 */
		void envoyerMessage();

		/**
		 *
		 * @param position
		 * @return
		 */
		virtual bool contient(sf::Vector2i position) = 0;

		/////////////////////////////////////////
		///	Methodes d'affichage
		/////////////////////////////////////////

		/**
		 *
		 * @param delta
		 */
		virtual void actualiser(float delta) = 0;
		/**
		 *
		 * @param fenetre
		 */
		virtual void afficher(sf::RenderWindow& fenetre) = 0;
};

#endif /* NEWELEMENT_HPP */
