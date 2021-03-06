/*
 * Jeu.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */
#ifndef JEU_HPP
#define JEU_HPP

#include <client/vue/Affichage.hpp>
#include <client/modele/Plateau.hpp>
#include <client/controleur/Controleur.hpp>
#include <client/vue/Scenes.hpp>
#include <client/ressources/Ressources.hpp>
#include <client/modele/Joueur.hpp>
#include <client/ressources/GestionnaireSons.hpp>
#include <commun/ReseauServeur.hpp>
#include <commun/ReseauClient.hpp>
#include <memory>

typedef std::unique_ptr<ReseauClient> ReseauPtr;

/**
 * \brief Conteneur du jeu
 *
 * Contient tout les éléments du jeu : Modèle, Contrôleur, Vue (Scene) et Affichage, ainsi que les Ressources du jeu
 */
class Jeu {
    private:
        /**
         * \brief Modèle
         *
         * Le modèle contenant les différentes données du jeu
         *
         * \see Modèle
         */
        Plateau modele;

        /**
         * \brief Contrôleur
         *
         * Le contrôleur faisant le lien entre la vue et le modèle
         *
         * \see Contrôleur
         */
        Controleur controleur;

        /**
         * \brief Le type de la scène demandée
         *
         * \see Scene
         */
        Scene::Type sceneDemandee;

        /**
         * \brief Scene
         *
         * La scène actuellement jouée à l'écran
         *
         * \see Scene
         */
        Scene::Ptr scene;

        /**
         * \brief Ressources
         *
         * Contient toutes les ressources du jeu
         *
         * \see Ressources
         */
        Ressources ressources;

        /**
         * \brief Horloge
         *
         * L'horloge permettant de gérer le temps dans l'application
         *
         * \see sf::Clock
         */
        sf::Clock horloge;

        /**
         * \brief Réseau
         *
         * La connexion réseau à un serveur
         *
         * \see ReseauClient
         */
        ReseauPtr reseau;

        /**
         * \brief le joueur venant du réseau
         */
        Joueur* joueur;

        /**
         * \brief le gestionnaire de sons de la partie
         */
        GestionnaireSons* gestionnaire;

        /**
         * \brief Si le réseau est actif ou non
         */
        bool reseauActif;

        /**
         * \brief Le réseau serveur
         */
        ReseauServeurPtr serveur;

        /**
         * \brief Le plateau serveur
         */
        PlateauServeurPtr plateauServeur;

        /**
         * \brief Change la scène si une nouvelle scène a été demandée
         */
        void changerScene();

    public:
        /**
         * \brief Constructeur
         *
         * Créé une nouvelle instance du Jeu
         */
        Jeu();

        /**
         * \brief Destructeur
         *
         * Détruit une instance précédemment créé du jeu
         */
        virtual ~Jeu();

        /**
         * \brief Remplace la scène actuelle par celle passée en paramètre
         *
         * Change la scène actuelle par la nouvelle passée en paramètre
         *
         * \param nouvelleScene la nouvelle scène
         */
        void changer(Scene::Type nouvelleScene);

        /**
         * \brief Lance le jeu
         *
         * Lance l'instance du jeu qui a été créé
         */
        void lancer();

        /**
         * \brief Quitter le jeu
         *
         * Quitte le jeu proprement
         */
        void quitter();

        void threadReseau();

        void lancerServeurGUI(unsigned int port, bool partieSolo);

        /**
         * \brief Récupère le modèle
         *
         * Permet d'accéderau modèle actuel
         *
         * \return le modèle actuel
         */
        Plateau& lirePlateau();
        /**
         * \brief Récupère le contrôleur
         *
         * Permet d'accéder au contrôleur actuel
         *
         * \return le contrôleur actuel
         */
        Controleur& lireControleur();

        /**
         * \brief Récupère les ressources
         *
         * Permet d'accéder aux différentes ressources du jeu
         *
         * \return les ressources du jeu
         */
        Ressources& lireRessources();

        GestionnaireSons* lireGestionnaire();

        ReseauPtr& lireReseau();
        Joueur* lireJoueur();
};

#endif /* JEU_HPP */
