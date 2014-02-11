/*
 * main.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include <iostream>
#include "Jeu.hpp"
#include "vue/Affichage.hpp"

int main() {
	Affichage::initialiser();

	Jeu jeu;

	jeu.lancer();

	Affichage::detruire();

	return (0);
}
