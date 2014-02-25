/*
 * BoutonConstruction.hpp
 *
 *  Created on: 24 févr. 2014
 *      Author: Soinou
 */

#ifndef BOUTONCONSTRUCTION_HPP
#define BOUTONCONSTRUCTION_HPP

#include "VuesPack.hpp"

#include <client/vue/gui/elements/generiques/Image.hpp>

class BoutonConstruction: public Element, public ObservateurSouris {
    private:

		Position cible;

        sf::RectangleShape cadre;
        sf::Sprite image;

        TypeCellule type;

        union {
                TypeVaisseau vaisseau;
                TypeBatiment batiment;
        };

    public:
        BoutonConstruction(Gui* gui, int id, int x, int y, int largeur,
                int hauteur);
        virtual ~BoutonConstruction();

        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);

        TypeCellule lireType();
        void ecrireType(TypeVaisseau type);
        void ecrireType(TypeBatiment type);

        TypeVaisseau lireVaisseau();
        TypeBatiment lireBatiment();

        void ecrireCible(Position position);
        Position lireCible();

        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);
};

#endif /* BOUTONCONSTRUCTION_HPP */
