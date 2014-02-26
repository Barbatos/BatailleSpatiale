/*
 * TexteFinDeJeu.hpp
 *
 *  Created on: 26 févr. 2014
 *      Author: Soinou
 */

#ifndef TEXTEFINDEJEU_HPP
#define TEXTEFINDEJEU_HPP

#include <SFML/Graphics/Text.hpp>

#include "GeneriquesPack.hpp"

/**
 * Oh god it's so dirty, it feels so exciting
 */
class TexteFinDeJeu: public Element {
    private:
        sf::Text texte;

    public:
        TexteFinDeJeu(Gui* gui, int id, int x, int y);
        virtual ~TexteFinDeJeu();

        // Héritées d'Element
        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);
};

#endif /* TEXTEFINDEJEU_HPP */
