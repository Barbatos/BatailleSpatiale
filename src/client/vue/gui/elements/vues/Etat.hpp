/*
* Etat.hpp
*
*  Created on: 23 jan. 2014
*      Author: Soinou
*/

#ifndef ETAT_HPP
#define ETAT_HPP

// Includes de nos classes
#include <utiles.hpp>

#include <client/vue/gui/evenements/Message.hpp>

// Pr� d�claration
class Jeu;
class AffichageDetails;

/**
 * \brief Etat de selection de case
 */
class Etat {
    private:
    /**
     * \brief Type de l'�tat
     */
    enum Type {
        Normal,
        Selection,
        Construction
    };

    /**
     * \brief Type de l'�tat
     */
    Type type;

    /**
     * \brief Pointeur vers les d�tails
     */
    AffichageDetails* details;

    /**
     * \brief Pointeur vers le jeu
     */
    Jeu* jeu;

    /**
     * \brief Appui case quand rien n'est selectionn�
     */
    void appuiCase_Normal(Message::MessageCellule message);

    /**
     * \brief Appui case quand une case est selectionn�e
     */
    void appuiCase_Selection(Message::MessageCellule message);

    /**
     * \brief Appui case quand un b�timent/vaisseau � construire est selectionn�
     */
    void appuiCase_Construction(Message::MessageCellule message);

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
     * \brief Appell�e par l'affichage plateau
     */
    void appuiCase(Message::MessageCellule message);

};

#endif