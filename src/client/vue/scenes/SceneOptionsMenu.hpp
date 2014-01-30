/*
 * SceneOptionsMenu.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Kowah
 */
#ifndef SCENEOPTIONSMENU_HPP_
#define SCENEOPTIONSMENU_HPP_
#include <client/vue/Scene.hpp>
#include <client/ressources/Ressources.hpp>

class SceneOptionsMenu : public Scene {
    private:
        enum Boutons {
            Musique,
            ChangerMusique,
            AugmenterMusique,
            BaisserMusique,
            Son,
            AugmenterSon,
            BaisserSon,
            Retour
        };

        Ressources::MusicPtr musique;

    public:
        /**
         * \brief Constructeur
         *
         * Créé une nouvelle instance de scène jeu options avec le jeu actuel
         *
         * \param jeu le jeu actuel
         */
        SceneOptionsMenu(Jeu& jeu);

        /**
         * \brief Destructeur
         *
         * Détruit l'instance précédemment créée de scène jeu options
         */
        virtual ~SceneOptionsMenu();

        // Héritée de Scene
        void surMessage(Message message);
};

#endif /* SCENEOPTIONSMENU_HPP */
