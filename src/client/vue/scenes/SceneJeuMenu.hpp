/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEUMENU_HPP
#define SCENEJEUMENU_HPP

// Includes de nos classes
#include <client/vue/Scene.hpp>

/**
 * \brief Scène du menu en jeu
 *
 * Scène du menu pause
 */
class SceneJeuMenu : public Scene
{
	private:
		enum Boutons { Retour, Sauvegarder, Charger, Options, QuitterPartie, QuitterJeu };

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance du menu pause
		 *
		 * \param jeu le jeu actuel
		 */
		SceneJeuMenu(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée du menu pause
		 */
		virtual ~SceneJeuMenu();

		// Héritée de Scene
		void surMessage(int nom, Scene::Message message);
};

#endif /* SCENEJEUMENU_HPP_ */
