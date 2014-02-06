/*
 * ListeServeurs.hpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#ifndef LISTESERVEURS_HPP
#define LISTESERVEURS_HPP

#include "GeneriquesPack.hpp"

class LigneServeur;

class ListeServeurs : public Element {
    private:
        std::list<LigneServeur*> lignes;

    public:
        ListeServeurs(Gui* gui, int id, int x, int y, int largeur, int hauteur);
        virtual ~ListeServeurs();
};

#endif /* LISTESERVEURS_HPP */
