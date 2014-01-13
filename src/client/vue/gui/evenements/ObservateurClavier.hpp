/*
 * ObservateurClavier.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef OBSERVATEURCLAVIER_HPP
#define OBSERVATEURCLAVIER_HPP

// Includes de la stdlib
#include <memory>

// Includes de la SFML
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/String.hpp>

class ObservateurClavier
{
	public:
		typedef std::shared_ptr<ObservateurClavier> Ptr;

		ObservateurClavier();
		virtual ~ObservateurClavier();

		virtual void pressionTouche(sf::Keyboard::Key touche) = 0;
		virtual void relachementTouche(sf::Keyboard::Key touche) = 0;
		virtual void entreeTexte(sf::Uint32 texte) = 0;
};

#endif /* OBSERVATEURCLAVIER_HPP */
