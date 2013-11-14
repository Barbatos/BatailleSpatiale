/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEU_HPP
#define SCENEJEU_HPP

#include <client/vue/Scene.hpp>
#include <client/modele/DetailBatiment.hpp>
#include <client/modele/DetailVaisseau.hpp>
#include <client/vue/vues/AffichageDetails.hpp>
#include <SFML/Graphics.hpp>
#include <client/vue/vues/AffichagePlateau.hpp>

/**
 * \brief Scène en jeu
 *
 * Scène affichant le plateau
 */
class SceneJeu : public Scene
{
	private:
		enum Elements
		{
			Pause = 0,
			Plateau,
		};

		AffichagePlateau plateau;

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
		void surMessage(int nom, Scene::Message message);
};

#endif /* SCENEJEU_HPP_ */
