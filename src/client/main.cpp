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
#include "client/ressources/Splash.hpp"

int main() {
    Affichage::initialiser();
    Splash::initialiser();
    Notification::initialiser();

    Jeu jeu;

    jeu.lancer();

    Notification::detruire();
    Splash::detruire();
    Affichage::detruire();

    return (0);
}
