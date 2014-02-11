/*
 * BarreStatut.hpp
 *
 *  Created on: 3 févr. 2014
 *      Author: Tendry
 */

#ifndef BARRESTATUT_HPP_
#define BARRESTATUT_HPP_

#include "GeneriquesPack.hpp"
#include <client/vue/gui/elements/generiques/BarreMesure.hpp>

/**
 * \brief Une barre affichant des infos et changeant de couleur en fonction du niveau critique
 */
class BarreStatut: public BarreMesure
{
	private:

		/**
		 * \brief la couleur de la barre au niveau normal
		 */
		sf::Color normale;

		/**
		 * \brief la couleur de la barre au niveau critique
		 */
		sf::Color critique;

	public:

		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle barre de statut avec les paramètres donnés
		 *
		 * \param gui le gui contenant la barre *
		 * \param x sa position en x
		 * \param y sa position en y
		 * \param largeur sa largeur
		 * \param hauteur sa hauteur
		 * \param la couleur de la barre de progression
		 * \param La couleur du niveau critique
		 */
		BarreStatut(Gui* gui, float x, float y, float largeur,
				float hauteur, sf::Color color, sf::Color color2);

		/**
		 * \brief destructeur
		 */
		virtual ~BarreStatut();

		void afficher();

		void setValeurMontree(int value);
};

#endif /* BARRESTATUT_HPP_ */
