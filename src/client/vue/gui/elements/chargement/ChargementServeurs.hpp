/*
 * ChargementServeurs.hpp
 *
 *  Created on: Feb 11, 2014
 *      Author: Soinou
 */

#ifndef CHARGEMENTSERVEURS_HPP
#define CHARGEMENTSERVEURS_HPP

#include "ChargementPack.hpp"

#include "../generiques/Label.hpp"
#include "../generiques/Animation.hpp"

/**
 * \brief Représente l'élément de chargement des serveurs
 *
 * Attends que la liste des serveurs soit chargée, puis envoie un message au gui le contenant
 */
class ChargementServeurs: public Element {
    private:
        /**
         * \brief Le texte à afficher
         */
        Label texte;

        /**
         * \brief L'animation de chargement
         */
        Animation image;

    public:

        ChargementServeurs(Gui* gui, int id, int x, int y, int largeur,
                int hauteur);
        virtual ~ChargementServeurs();

        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);
};

#endif /* CHARGEMENTSERVEURS_HPP */
