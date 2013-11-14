/*
 * Plateau.hpp
 *
 *  Created on: 11 nov. 2013
 *      Author: Soinou
 */

#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "DetailBatiment.hpp"
#include "DetailVaisseau.hpp"
#include "DetailEvenement.hpp"
#include "Position.hpp"

class Plateau
{
	private:
		int xVaisseau;
		int yVaisseau;

	public:
		Plateau();
		virtual ~Plateau();

		bool possedeEvenement(Position p);
		bool possedeVaisseau(Position p);
		bool possedeBatiment(Position p);

		DetailVaisseau getVaisseau(Position p);
		DetailBatiment getBatiment(Position p);
		DetailEvenement getEvenement(Position p);

		int getTailleX();
		int getTailleY();

		void deplacerVaisseau(Position ancienne, Position nouvelle);
};

#endif /* PLATEAU_HPP */
