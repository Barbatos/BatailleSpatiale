/*
 * ListeServeurs.cpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#include "ListeServeurs.hpp"

#include "LigneServeur.hpp"

ListeServeurs::ListeServeurs(Gui* gui, int id, int x, int y, int largeur, int hauteur)
                : Element(gui, id), lignes() {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);
}

ListeServeurs::~ListeServeurs() {
}
