/*
 * LigneServeur.hpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Soinou
 */

#ifndef LIGNESERVEUR_HPP
#define LIGNESERVEUR_HPP

#include "GeneriquesPack.hpp"

class LigneServeur: public Element, public ObservateurSouris {
    private:
        const Serveur& serveur;
        sf::RectangleShape bouton;
        sf::Text texteBouton;
        sf::RectangleShape cadre;
        sf::Text texteCadre;

    public:
        LigneServeur(Gui* gui, int id, int x, int y, int largeur, int hauteur,
                const Serveur& serveur, sf::View* vue);
        virtual ~LigneServeur();

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

#endif /* LIGNESERVEUR_HPP */
