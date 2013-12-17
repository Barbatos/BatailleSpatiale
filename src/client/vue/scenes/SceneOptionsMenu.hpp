/*
 * SceneOptionsMenu.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */
#ifndef SCENEOPTIONSMENU_HPP_
#define SCENEOPTIONSMENU_HPP_
#include <client/vue/Scene.hpp>
class SceneOptionsMenu :
	public Scene
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
		SceneOptionsMenu(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée de scène jeu options
		 */
		virtual ~SceneOptionsMenu();

		// Héritée de Scene
		void surMessage(int id);
};

#endif /* SCENEOPTIONSMENU_HPP */
