/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEUOPTIONS_HPP
#define SCENEJEUOPTIONS_HPP

#include <client/vue/Scene.hpp>

/**
 * \brief Scène du menu des options depuis le jeu
 *
 * Écran des options du jeu
 */
class SceneJeuOptions : public Scene
{
	private:
		enum Boutons
		{
			Retour
		};

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance de scène jeu options avec le jeu actuel
		 *
		 * \param jeu le jeu actuel
		 */
		SceneJeuOptions(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée de scène jeu options
		 */
		virtual ~SceneJeuOptions();

		// Héritée de Scene
		void surMessage(int nom, Scene::Message message);
};

#endif /* SCENEJEUOPTIONS_HPP_ */
