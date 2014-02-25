/*
 * AffichageConstructions.hpp
 *
 *  Created on: 26 janv. 2014
 *      Author: Gabriel
 */

#ifndef AFFICHAGECONSTRUCTIONS_HPP
#define AFFICHAGECONSTRUCTIONS_HPP

#include <list>

#include <SFML/Graphics.hpp>

#include "../../Element.hpp"

class BoutonConstruction;

class AffichageConstructions: public Element {
    private:
        std::list<BoutonConstruction*> vaisseaux;
        std::list<BoutonConstruction*> batiments;

        /**
         * La position cible de la construction
         */
        Position cible;

    public:
        AffichageConstructions(Gui* gui, int id, int x, int y, int largeur,
                int hauteur);
        virtual ~AffichageConstructions();

        // Héritées d'Element
        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);

        void changerCible(Position cible);

        Position lireCible();

        void ajouterBouton(TypeVaisseau vaisseau, int x, int y, int largeur,
                int hauteur);
        void ajouterBouton(TypeBatiment batiment, int x, int y, int largeur,
                int hauteur);

        void ecrireVaisseauxVisibles(bool visible);
        void ecrireBatimentsVisibles(bool visible);
};

#endif /* AFFICHAGECONSTRUCTIONS_HPP */
