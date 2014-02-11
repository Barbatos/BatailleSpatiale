/*
 * BoutonDeplacementPlateau.hpp
 *
 *  Created on: 5 déc. 2013
 *      Author: Thornydre
 */

#ifndef BOUTONDEPLACEMENTPLATEAU_HPP
#define BOUTONDEPLACEMENTPLATEAU_HPP

// Includes de nos classes
#include "VuesPack.hpp"
#include <client/vue/gui/elements/generiques/Label.hpp>

/**
 * \brief Bouton simple permettant de déplacer le plateau
 */
class BoutonDeplacementPlateau : public Element, public ObservateurSouris {
    private:
        /**
         * \brief Rectangle de fond
         */
        sf::RectangleShape fond;

    public:
        /**
         * \brief Constructeur
         *
         * \param gui le gui contenant le bouton
         * \param id l'id du bouton
         * \param x la position en x du bouton
         * \param y la position en y du bouton
         * \param largeur la largeur du bouton
         * \param hauteur la hauteur du bouton
         */
        BoutonDeplacementPlateau(Gui* gui, int id, float x, float y, float largeur, float hauteur);

        /**
         * \brief Destructeur
         */
        virtual ~BoutonDeplacementPlateau();

        // Héritées d'Element
        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);

        // Héritées d'ObservateurSouris
        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);
};

#endif /* BOUTONDEPLACEMENTPLATEAU_HPP */
