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
#include "evenements/ObservateurSouris.hpp"
#include "evenements/ObservateurClavier.hpp"

// Pré-déclarations
class Gui;

/**
 * \brief Représente un élément graphique, appartenant à un Gui, et affiché à l'écran
 */
class Element {
private:
	///////////////////////////////////////////////////
	///	<!-- Général -->
	///////////////////////////////////////////////////

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

	///////////////////////////////////////////////////
	///	<!-- Observateurs -->
	///////////////////////////////////////////////////

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
	///////////////////////////////////////////////////
	///	<!-- Divers -->
	///////////////////////////////////////////////////

	/**
	 * \brief Si l'élement est survolé
	 */
	bool survol;

	/**
	 * \brief Si l'élement est appuyé
	 */
	bool appui;

	/**
	 * \brief La vue où se trouve l'élement
	 */
	sf::View* vue;

public:
	///////////////////////////////////////////////////
	///	<!-- Typedefs -->
	///////////////////////////////////////////////////

	/**
	 * \brief Version shared_ptr de l'élement
	 */
	typedef std::shared_ptr<Element> Ptr;

	///////////////////////////////////////////////////
	///	<!-- Constructeurs/Destructeurs -->
	///////////////////////////////////////////////////

	/**
	 * \brief Constructeur
	 *
	 * \param gui un pointeur vers le gui contenant l'élement
	 * \param id l'id de l'élement
	 */
	Element(Gui* gui, int id);

	/**
	 * \brief Destructeur
	 */
	virtual ~Element();

	///////////////////////////////////////////////////
	///	<!-- Methodes observateurs -->
	///////////////////////////////////////////////////

	/**
	 * \brief Retourne un pointeur vers l'observateur souris de l'élement
	 *
	 * \return l'observateur souris de l'élement, ou nullptr si il n'y en a pas
	 */
	ObservateurSouris::Ptr lireSouris();

	/**
	 * \brief Retourne un pointeur vers l'observateur clavier de l'élement
	 *
	 * \return l'observateur clavier de l'élement, ou nullptr si il n'y en a pas
	 */
	ObservateurClavier::Ptr lireClavier();

	/**
	 * \brief Change l'observateur souris de l'élement
	 *
	 * \param observateur le nouvel observateur souris de l'élement
	 */
	void enregistrerSouris(ObservateurSouris::Ptr observateur);

	/**
	 * \brief Change l'observateur clavier de l'élement
	 *
	 * \param observateur le nouvel observateur clavier de l'élement
	 */
	void enregistrerClavier(ObservateurClavier::Ptr observateur);

	/**
	 * \brief Retourne si l'élement a défini l'observateur souris ou non
	 *
	 * \return true si l'observateur souris est défini, false sinon
	 */
	bool observeSouris();

	/**
	 * \brief Retourne si l'élement a défini l'observateur clavier ou non
	 *
	 * \return true si l'observateur clavier est défini, false sinon
	 */
	bool observeClavier();

	///////////////////////////////////////////////////
	///	<!-- Methodes générales -->
	///////////////////////////////////////////////////

	/**
	 * \brief Retourne l'id de l'élement
	 *
	 * \return l'id de l'élement
	 */
	int lireId();

	/**
	 * \brief Retourne un pointeur vers le gui contenant l'élement
	 *
	 * \return un pointeur vers le gui contenant l'élement
	 */
	Gui* lireGui();

	/**
	 * \brief Change l'id de l'élement
	 *
	 * \param id le nouvel id de l'élement
	 */
	void ecrireId(int id);

	/**
	 * \brief Change le gui de l'élement
	 *
	 * \param gui le nouveau gui de l'élement
	 */
	void ecrireGui(Gui* gui);

	/**
	 * \brief Retourne la taille de l'élement
	 *
	 * \return la taille de l'élement
	 */
	sf::Vector2f lireTaille();

	/**
	 * \brief Retourne la position de l'élement
	 *
	 * \return la position de l'élement
	 */
	sf::Vector2f lirePosition();

	/**
	 * \brief Change la taille de l'élement
	 *
	 * \param taille la nouvelle taille de l'élement
	 */
	void ecrireTaille(sf::Vector2f taille);

	/**
	 * \brief Change la taille de l'élement
	 *
	 * Appelle ecrireTaille(sf::Vector2f) avec la largeur et la hauteur
	 * données sous forme d'un sf::Vector2f
	 *
	 * \param largeur la nouvelle largeur de l'élement
	 * \param hauteur la nouvelle hauteur de l'élement
	 */
	void ecrireTaille(float largeur, float hauteur);

	/**
	 * \brief Change la position de l'élement
	 *
	 * \param position la nouvelle position de l'élement
	 */
	void ecrirePosition(sf::Vector2f position);

	/**
	 * \brief Change la position de l'élement
	 *
	 * Appelle ecrirePosition(sf::Vector2f) avec x et y
	 * données sous forme d'un sf::Vector2f
	 *
	 * \param x la nouvelle position en x de l'élement
	 * \param y la nouvelle position en y de l'élement
	 */
	void ecrirePosition(float x, float y);

	/**
	 * \brief Change la zone de l'élement
	 *
	 * Appelle ecrireTaille(float, flaot) et ecrirePosition(float, float)
	 * avec les différents composants de la zone séparés
	 *
	 * \param zone la nouvelle zone de l'élement
	 */
	void ecrireZone(sf::FloatRect zone);

	///////////////////////////////////////////////////
	///	<!-- Methodes diverses -->
	///////////////////////////////////////////////////

	/**
	 * \brief Retourne si l'élement est survolé ou non
	 *
	 * \return si l'élement est survolé ou non
	 */
	bool lireSurvol();

	/**
	 * \brief Retourne si l'élement est appuyé ou non
	 *
	 * \return si l'élement est appuyé ou non
	 */
	bool lireAppui();

	/**
	 * \brief Retourne la vue où se trouve l'élement
	 *
	 * \return la vue où se trouve l'élement
	 */
	sf::View* lireVue();

	/**
	 * \brief Retourne si l'élement possède une vue définie ou non
	 *
	 * \return si l'élement possède une vue définie ou non
	 */
	bool possedeVue();

	/**
	 * \brief Change si l'élement est survolé ou non
	 *
	 * \param survol si l'élement est survolé ou non
	 */
	void ecrireSurvol(bool survol);

	/**
	 * \brief Change si l'élement est appuyé ou non
	 *
	 * \param appui si l'élement est appuyé ou non
	 */
	void ecrireAppui(bool appui);

	/**
	 * \brief Change la vue de l'élement
	 *
	 * \param vue la nouvelle vue de l'élement
	 */
	void ecrireVue(sf::View* vue);

	/**
	 * \brief Envoie un message au gui contenant l'élement
	 */
	void envoyerMessage();

	/**
	 * \brief Retourne si l'élement contient ou non la position donnée
	 *
	 * Méthode virtuelle à implémenter dans les éventuels fils
	 *
	 * \param position la position à tester
	 * \return si cette position est dans l'élement ou non
	 */
	virtual bool contient(sf::Vector2i position) = 0;

	///////////////////////////////////////////////////
	///	<!-- Methodes d'affichage -->
	///////////////////////////////////////////////////

	/**
	 * \brief Actualise l'affichage de l'élement
	 *
	 * \param delta le temps écoulé depuis le dernier appel de cette fonction
	 */
	virtual void actualiser(float delta) = 0;

	/**
	 * \brief Affiche l'élement sur la fenêtre donnée
	 *
	 * \param fenetre la fenêtre où afficher l'élement
	 */
	virtual void afficher(sf::RenderWindow& fenetre) = 0;
};

#endif /* NEWELEMENT_HPP */
