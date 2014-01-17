/*
 * ObservateurSouris.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef OBSERVATEURSOURIS_HPP
#define OBSERVATEURSOURIS_HPP

// Includes de la stdlib
#include <memory>

// Includes de la SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class ObservateurSouris {
    public:
        typedef std::shared_ptr<ObservateurSouris> Ptr;

        ObservateurSouris();
        virtual ~ObservateurSouris();

        virtual void clicSouris(bool clicDroit) = 0;
        virtual void pressionSouris(sf::Mouse::Button bouton) = 0;
        virtual void relachementSouris(sf::Mouse::Button bouton) = 0;
        virtual void entreeSouris(sf::Vector2f position) = 0;
        virtual void sortieSouris(sf::Vector2f position) = 0;
        virtual void moletteSouris(int delta) = 0;
};

#endif /* OBSERVATEURSOURIS_HPP */
