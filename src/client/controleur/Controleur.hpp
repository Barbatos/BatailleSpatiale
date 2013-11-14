/*
 * Controleur.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP

// Pré-Déclaration de la classe Modèle
class Plateau;

/**
 * \brief Fait le lien entre le modèle et la vue
 */
class Controleur
{
	private:
		/**
		 * \brief Référence vers le modèle actuel
		 */
		Plateau& modele;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Instancie un nouveau Contrôleur avec le modèle passé en paramètre
		 *
		 * \param modele le modèle à lier
		 */
		Controleur(Plateau& modele);

		/**
		 * \brief Destructeur
		 *
		 * Détruit l'instance précédemment créée du Contrôleur
		 */
		virtual ~Controleur();
};

#endif /* CONTROLEUR_HPP_ */
