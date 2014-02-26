/*
 * SceneFinDeJeu.hpp
 *
 *  Created on: 26 févr. 2014
 *      Author: Soinou
 */

#ifndef SCENEFINDEJEU_HPP
#define SCENEFINDEJEU_HPP

#include "ScenesPack.hpp"

class SceneFinDeJeu: public Scene {
    public:
        SceneFinDeJeu(Jeu& jeu);
        virtual ~SceneFinDeJeu();

        void surMessage(Message message);
};

#endif /* SCENEFINDEJEU_HPP */
