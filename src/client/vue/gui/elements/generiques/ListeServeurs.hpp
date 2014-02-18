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

class ListeServeurs: public Element {
    private:
        std::list<LigneServeur*> lignes;
        sf::View vue;

    public:
        ListeServeurs(Gui* gui, int id, int x, int y, int largeur, int hauteur);
        virtual ~ListeServeurs();

        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);
};

#endif /* LISTESERVEURS_HPP */
