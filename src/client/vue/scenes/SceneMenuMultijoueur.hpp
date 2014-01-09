/*
 * SceneMenuMultijoueur.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */

#ifndef SCENEMENUMULTIJOUEUR_HPP_
#define SCENEMENUMULTIJOUEUR_HPP_

#include <client/vue/Scene.hpp>

/**
 * \brief Scène du menu de création de partie Multijoueur
 *
 * Écran de création d'une partie Multijoueur
 */
class SceneMenuMultijoueur :
	public Scene
{
	private:
		/**
		 * \brief Les différents boutons de la scène
		 */
		enum Boutons
		{
			Multijoueur, //!< Lancer une partie multijoueur
			Retour
		};

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance de scène menu multijoueur avec le jeu actuel
		 *
		 * \param jeu le jeu actuel
		 */
		SceneMenuMultijoueur(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée de scène menu multijoueur
		 */
		virtual ~SceneMenuMultijoueur();

		// Héritée de Scene
		void surMessage(int id);
};

#endif /* SCENEMENUMULTIJOUEUR_HPP_ */
