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
 * \brief Sc�ne affich�e lors du chargement d'une partie multijoueur
 */
class SceneChargementJeuMulti : public Scene {
public:
    /**
     * \brief Constructeur par d�faut
     *
     * \param jeu le jeu actuel
     */
    SceneChargementJeuMulti(Jeu& jeu);

    /**
     * \brief Destructeur
     */
    virtual ~SceneChargementJeuMulti();

    // H�rit�e de Scene
    void surMessage(Message message);
};

#endif /* SCENECHARGEMENTJEUMULTI_HPP */
