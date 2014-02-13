/*
 * main.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include <iostream>
#include "Jeu.hpp"
#include "vue/Affichage.hpp"
#include "utile/Notification.hpp"

int main() {
    Affichage::initialiser();
    Notification::initialiser();

    Jeu jeu;

    jeu.lancer();

    Notification::detruire();
    Affichage::detruire();

    return (0);
}
