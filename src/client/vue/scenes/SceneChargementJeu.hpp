/*
 * SceneChargementJeu.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTJEU_HPP
#define SCENECHARGEMENTJEU_HPP

#include "ScenesPack.hpp"

/**
 * \brief Scène affichée lors du chargement d'une partie solo
 */
class SceneChargementJeu : public Scene {
public:
    /**
     * \brief Constructeur
     *
     * \param jeu le jeu actuel
     */
    SceneChargementJeu(Jeu& jeu);

    /**
     * \brief Destructeur
     */
    virtual ~SceneChargementJeu();

    // Héritée de Scene
    void surMessage(Message message);
};

#endif /* SCENECHARGEMENTJEU_HPP */
