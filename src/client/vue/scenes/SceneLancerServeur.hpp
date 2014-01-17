/*
 * SceneLancerServeur.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: Barbatos
 */

#ifndef SCENELANCERSERVEUR_HPP
#define SCENELANCERSERVEUR_HPP

#include <client/vue/Scene.hpp>

class ZoneTexte;

/**
 * \brief Scène du menu de création d'un serveur de jeu
 *
 * Écran de création d'un serveur
 */
class SceneLancerServeur : public Scene {
    private:
        /**
         * \brief Les différents boutons de la scène
         */
        enum Boutons {
            Port,
            Serveur,
            Retour
        };

        ZoneTexte* port;

    public:
        /**
         * \brief Constructeur
         *
         * Créé une nouvelle instance de scène serveur de jeu
         *
         * \param jeu le jeu actuel
         */
        SceneLancerServeur(Jeu& jeu);

        /**
         * \brief Destructeur
         *
         * Détruit l'instance précédemment créée de scène serveur de jeu
         */
        virtual ~SceneLancerServeur();

        // Héritée de Scene
        void surMessage(Message message);
};

#endif /* SCENELANCERSERVEUR_HPP */
