/*
 * SceneMenuSolo.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEMENUSOLO_HPP
#define SCENEMENUSOLO_HPP

#include <client/vue/Scene.hpp>

class ZoneTexte;

/**
 * \brief Scène du menu de création de partie Solo
 *
 * Écran de création d'une partie Solo
 */
class SceneMenuSolo : public Scene
{
	private:
		/**
		 * \brief Les différents boutons de la scène
		 */
		enum Boutons {
			Solo,//!< Lancer une partie Solo
			Retour,
			Ip,
			Port
		};

		ZoneTexte* ip;
		ZoneTexte* port;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance de scène menu solo avec le jeu actuel
		 *
		 * \param jeu le jeu actuel
		 */
		SceneMenuSolo(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée de scène menu solo
		 */
		virtual ~SceneMenuSolo();

		// Héritée de Scene
		void surMessage(int nom, Scene::Message message);
};

#endif /* SCENEMENUSOLO_HPP_ */
