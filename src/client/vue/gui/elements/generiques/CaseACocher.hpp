/*
 * CaseACocher.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Tahiry
 */

#ifndef CASEACOCHER_HPP
#define CASEACOCHER_HPP

#include "GeneriquesPack.hpp"
#include "Label.hpp"

/**
 * \brief Case à cocher, indique qu'un élément est selectioné
 *
 */
class CaseACocher : public Element, public ObservateurSouris {
    private:

		/**
		 * \brief la boite de la case a cocher
		 */
        sf::RectangleShape boite;

        /**
         * \brief indique si la case est cliquee
         */
        bool clique;

        /**
         * \brief le texte associé à la case
         */
        Label texte;

        /**
         * \brief la couleur quand la case est cochee
         */
        sf::Color coche;

        /**
        * \brief la couleur quand la case n'est pas cochee
        */
        sf::Color nonCoche;

    public:

        /**
         * \brief Constructeur de la cache à cocher
         * \param gui le gui de l'objet
         * \param id l'id de la case
         * \param x la position x dans l'espace
         * \param y la position y dans l'espace
         * \param largeur la largeur de la boite
         * \param hauteur la hauteur de la boite
         * \param txt le texte associé à la case
         */
        CaseACocher(Gui* gui, int id, int x, int y, float largeur, float hauteur,
        		std::string txt, sf::Color one, sf::Color two);
        virtual ~CaseACocher();

        /**
         * \brief indique si la case est cochee
         */
        bool estCoche();

        /**
         * \brief coche la case
         */
        void cocher();

        void actualiser(float delta);
        void afficher(sf::RenderWindow& affichage);
        bool contient(sf::Vector2i position);

        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);
};

#endif /* CASEACOCHER_HPP */
