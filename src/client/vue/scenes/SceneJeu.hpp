/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEU_HPP
#define SCENEJEU_HPP

#include <client/vue/Scene.hpp>
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
#include <client/modele/structures/DetailBatiment.hpp>
#include <client/modele/structures/DetailVaisseau.hpp>
#include <client/vue/vues/AffichageDetails.hpp>
>>>>>>> 3ae1e68ab228005609523908f02572fda1ed3a8d
#include <SFML/Graphics.hpp>
#include <client/vue/vues/AffichagePlateau.hpp>

/**
 * \brief Scène en jeu
 *
 * Scène affichant le plateau
 */
class SceneJeu :
	public Scene
{
	private:
		enum Elements
		{
			Pause = 0, Plateau, Droite, Gauche, Haut, Bas
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
		void surMessage(int nom);
};

#endif /* SCENEJEU_HPP */
