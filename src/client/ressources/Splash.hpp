/*
 * Splash.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef SPLASH_HPP
#define SPLASH_HPP

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

class Splash
{
	private:
		Splash();

		static Splash instance;

		sf::RenderWindow fenetre;
		sf::Font police;
		sf::Text label;

		std::string texte;
		int valeur;
		int maxi;

		bool fin;

	public:
		virtual ~Splash();

		void lancer();

		void fermer();

		void actualiser();

		void dessiner();

		std::string lireTexte();

		int lireValeur();

		int lireMaxi();

		void changerTexte(std::string texte);

		void changerValeur(int valeur);

		void changerMaxi(int maxi);

		static Splash& lireInstance();
};

#endif /* SPLASH_HPP */
