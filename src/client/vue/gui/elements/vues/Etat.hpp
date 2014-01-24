/*
 * Etat.hpp
 *
 *  Created on: 23 jan. 2014
 *      Author: Soinou
 */

#ifndef ETAT_HPP
#define ETAT_HPP

// Includes de la libstd
#include <queue>

// Includes de nos classes
#include <utiles.hpp>
#include <client/vue/gui/evenements/Message.hpp>

// Pré déclaration
class Jeu;
class AffichageDetails;

/**
 * \brief Etat de selection de case
 */
class Etat {
    private:
        /**
         * \brief Type de l'état
         */
        enum Type {
            Normal,
            Selection,
            Construction
        };

        /**
         * \brief Type de l'état
         */
        Type type;

        /**
         * \brief Pointeur vers les détails
         */
        AffichageDetails* details;

        /**
         * \brief Pointeur vers le jeu
         */
        Jeu* jeu;

        /**
         * \brief File des messages de case
         */
        std::queue<Message::MessageCellule> messages;

        /**
         * \brief Appui case quand rien n'est selectionné
         */
        void appuiNormal();

        /**
         * \brief Appui case quand une case est selectionnée
         */
        void appuiSelection();

        /**
         * \brief Appui case quand un bâtiment/vaisseau à construire est selectionné
         */
        void appuiConstruction();

    public:

        /**
         * \brief Constructeur
         */
        Etat(AffichageDetails* details, Jeu* jeu);

        /**
         * \brief Destructeur
         */
        virtual ~Etat();

        /**
         * \brief Appellée par l'affichage plateau lorsqu'une case est appuyée
         */
        void appuiCase(Message::MessageCellule message);

        /**
         * \brief Appui sur le plateau, pour dire qu'on peut commencer à traiter les messages reçus
         */
        void appuiPlateau();

};

#endif
