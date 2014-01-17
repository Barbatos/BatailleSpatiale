/*
 * SceneChargementJeu.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTJEU_HPP
#define SCENECHARGEMENTJEU_HPP

#include "ScenesPack.hpp"
#include <client/vue/gui/evenements/Message.hpp>

class SceneChargementJeu : public Scene {
    private:
        enum Elements {

        };

    public:
        SceneChargementJeu(Jeu& jeu);
        virtual ~SceneChargementJeu();

        void surMessage(Message message);
};

#endif /* SCENECHARGEMENTJEU_HPP */
