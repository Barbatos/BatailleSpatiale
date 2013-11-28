/*
 * SceneMenuPrincipal.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef SCENEMENUPRINCIPAL_HPP
#define SCENEMENUPRINCIPAL_HPP

// Includes de nos classes
#include <client/vue/Scene.hpp>
#include <client/ressources/Ressources.hpp>

/**
 * \brief Scène du Menu principal
 *
 * Scène du Menu Principal, premier écran montré
 */
class SceneMenuPrincipal : public Scene
{
	private:
		/**
		 * \brief Petite musique à jouer
		 *
		 * Une musique jouée pendant la scène
		 */
		MusicPtr musique;

		/**
		 * \brief Les différents boutons de la scène
		 */
		enum Boutons
		{
			Solo,//!< Lancer une partie Solo
			Multi,//!< Lancer une partie Multi
			Quitter,//!< Quitter la partie
			Musique,//!< Jouer ou mettre en pause la musique
			Options,//!< Options du jeu
			Serveur //!< Lancer un serveur 
		};

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance de menu principal avec le jeu actuel
		 *
		 * \param jeu le jeu actuel
		 */
		SceneMenuPrincipal(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée du Menu Principal
		 */
		virtual ~SceneMenuPrincipal();

		// Héritée de Scene
		void surMessage(int nom, Scene::Message message);
};

#endif /* SCENEMENUPRINCIPAL_HPP */
