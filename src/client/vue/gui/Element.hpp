/*
 * Element.hpp
 *
 *  Created on: 6 oct. 2013
 *      Author: Soinou
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

// Includes de la libstd
#include <memory>
#include <string>

// Includes de la SFML
#include <SFML/Graphics.hpp>

// Includes de nos classes
#include <client/vue/Scene.hpp>

// Pré-déclarations
class Affichage;

// Typedefs
typedef std::unique_ptr<Scene> ScenePtr;

/**
 * \brief Définit un élément graphique
 */
class Element
{
	protected:
		/**
		 * \brief Le nom de l'élement
		 *
		 * Indique le nom de l'élément
		 */
		int nom;

		/**
		 * \brief La zone de l'élément
		 *
		 * La position et la taille de l'élément
		 */
		sf::FloatRect zone;

		/**
		 * \brief Le parent de l'élément
		 *
		 * Pointeur vers le parent de l'élément
		 *
		 * \see Scene
		 */
		ScenePtr parent;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé un nouvel élément avec le nom donné et la zone donnée
		 *
		 * \param nom le nom de l'élément
		 * \param x la position en x de l'élement
		 * \param y la position en y de l'élément
		 * \param largeur la largeur de l'élément
		 * \param hauteur la hauteur de l'élément
		 */
		Element(int nom, int x, int y, int largeur,
				int hauteur);

		/**
		 * \brief Constructeur
		 *
		 * Créé un nouvel élément avec le nom donné et la zone donnée
		 *
		 * \param nom le nom de l'élément
		 * \param zone la zone de l'élément
		 */
		Element(int nom, sf::FloatRect zone);

		/**
		 * \brief Destructeur
		 *
		 * Détruit une instance précédemment créé d'un élément
		 */
		virtual ~Element();

		/**
		 * \brief Initialise l'élément
		 *
		 * Appelé juste après changerParent(). Cette fonction est donc éxecutée lorsque le parent
		 * de l'élément a été défini.
		 */
		virtual void initialiser() = 0;

		/**
		 * \brief Actualise l'élément
		 *
		 * Met à jour l'élément selon le temps donné en paramètre
		 *
		 * \param delta le temps qui s'est écoulé depuis le dernier appel à la fonction
		 */
		virtual void actualiser(float delta) = 0;

		/**
		 * \brief Affiche l'élément à l'écran
		 *
		 * Affiche l'élément sur l'affichage donné en paramètre
		 *
		 * \param affichage l'affichage où dessiner l'élément
		 * \see Affichage
		 */
		virtual void afficher(Affichage& affichage) = 0;

		/**
		 * \brief Change le parent de l'élément
		 *
		 * Indique à l'élément qui est son parent, c'est à dire à qui il doit envoyer ses messages
		 *
		 * \param parent le parent de l'élément
		 * \see Scene
		 */
		virtual void changerParent(Scene* parent);

		/**
		 * \brief Envoie un message au parent de l'élément
		 *
		 * Fait suivre un message au parent précédemment défini de l'élément
		 *
		 * \param message le message à faire suivre
		 * \see Scene::Message
		 */
		void envoyerMessage(Scene::Message message);

		/**
		 * \class Element
		 *
		 * élément générique affiché dans une scène.
		 *
		 * Possède une fonction permettant d'envoyer un message qui sera traité par la scène parente,
		 * et deux fonctions à implémenter lors d'un héritage : actualiser() et afficher()
		 *
		 * Exemple de création de nouvel élément :
		 *
		 \code
		 class NouvelElement : public Element
		 {
			 public:
				 NouvelElement(std::string nom);
				 ~NouvelElement() { }

				 void actualiser(float delta);
				 void afficher(Affichage& affichage);
		 }

		 NouvelElement::NouvelElement(std::string nom) : Element(nom)
		 {
		 }

		 void NouvelElement::actualiser(float delta)
		 {
			 // Mise à jour de l'élément

			 // On a besoin de faire passer un message à la scène :
			 envoyerMessage(Scene::NouveauMessage);
		 }

		 void NouvelElement::afficher(Affichage& affichage)
		 {
			 // Affichage de l'élément
			 affichage.draw(quelqueChose);
		 }
		 \endcode
		 */
};

#endif /* ELEMENT_HPP_ */
