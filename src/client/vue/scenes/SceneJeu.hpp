/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEU_HPP
#define SCENEJEU_HPP

#include <client/vue/Scene.hpp>

#include <client/vue/vues/AffichagePlateau.hpp>

#include <client/vue/vues/AffichageDetails.hpp>

/**
 * \brief Scène en jeu
 *
 * Scène affichant le plateau
 */
class SceneJeu :
	public Scene
{
	private:
		/**
		 *
		 */
		enum Elements
		{
			Pause, //!<
			Plateau, //!<
			Droite, //!<
			Gauche, //!<
			Haut, //!<
			Bas, //!<
			Details //!<
		};

		/**
		 *
		 */
		AffichagePlateau::Ptr plateau;

		/**
		 *
		 */
		AffichageDetails::Ptr details;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance de scène de jeu
		 *
		 * \param jeu le jeu actuel
		 */
		SceneJeu(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée de scène de jeu
		 */
		virtual ~SceneJeu();

		// Héritée de Scene
		void surMessage(int nom);
};

#endif /* SCENEJEU_HPP */
