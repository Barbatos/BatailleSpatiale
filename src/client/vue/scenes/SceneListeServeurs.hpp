/*
 * SceneListeServeurs.hpp
 *
 *  Created on: 18 févr. 2014
 *      Author: Soinou
 */

#ifndef SCENELISTESERVEURS_HPP
#define SCENELISTESERVEURS_HPP

#include <client/Jeu.hpp>
#include <client/vue/Scene.hpp>

class SceneListeServeurs: public Scene {
    public:
        SceneListeServeurs(Jeu& jeu);
        virtual ~SceneListeServeurs();

        void surMessage(Message message);
};

#endif /* SCENELISTESERVEURS_HPP */
