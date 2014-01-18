/*
 * SceneChargementJeuMulti.hpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTJEUMULTI_HPP
#define SCENECHARGEMENTJEUMULTI_HPP

#include "ScenesPack.hpp"

/**
 * \brief Scène affichée lors du chargement d'une partie multijoueur
 */
class SceneChargementJeuMulti : public Scene {
public:
    /**
     * \brief Constructeur par défaut
     *
     * \param jeu le jeu actuel
     */
    SceneChargementJeuMulti(Jeu& jeu);

    /**
     * \brief Destructeur
     */
    virtual ~SceneChargementJeuMulti();

    // Héritée de Scene
    void surMessage(Message message);
};

#endif /* SCENECHARGEMENTJEUMULTI_HPP */
