/*
 * AffichageCase.hpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGECASE_HPP
#define AFFICHAGECASE_HPP

// Include du 'pack' vue
#include "VuesPack.hpp"

#include <client/vue/gui/elements/generiques/Animation.hpp>

/**
 * \brief Représente l'affichage d'une case du plateau
 */
class AffichageCase: public Element, public ObservateurSouris {
    private:
        /**
         * \brief L'image affichée sur la case
         */
        sf::Sprite image;

        /**
         * \brief Le fond de la case
         */
        sf::CircleShape fond;

        /**
         * \brief La position associée à la case
         */
        Position position;

        /**
         * \brief Si la case est sélectionnée
         */
        bool selectionne;

        /**
         * L'animation d'attaque
         */
        Animation* animation;

    public:
        /**
         * \brief Version unique_ptr de l'affichage case
         */
        typedef std::shared_ptr<AffichageCase> Ptr;

        /**
         * \brief Constructeur
         */
        AffichageCase(Gui* gui, int id, float x, float y, float taille,
                Position position, sf::View* vuePlateau);

        /**
         * \brief Destructeur
         */
        virtual ~AffichageCase();

        /**
         * \brief Retourne la position sur le plateau de la case
         *
         * \return la position sur le plateau de la case
         */
        Position lirePositionPlateau();

        /**
         * \brief Retourne si la case est sélectionnée
         *
         * \return si la case est sélectionnée
         */
        bool lireSelectionne();

        /**
         * \brief Change la position sur le plateau de la case
         *
         * \param position la nouvelle position sur le plateau de la case
         */
        void ecrirePositionPlateau(Position position);

        // Héritées d'Element
        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);

        // Héritées d'observateur souris
        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);
};

#endif /* AFFICHAGECASE_HPP */
