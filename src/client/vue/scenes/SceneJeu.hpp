/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEU_HPP
#define SCENEJEU_HPP

#include "ScenesPack.hpp"

// Pré-déclarations
class AffichagePlateau;
class AffichageDetails;

/**
 * \brief Scène en jeu
 *
 * Scène affichant le plateau
 */
class SceneJeu : public Scene {
private:
    /**
     * \brief L'affichage du plateau
     */
    AffichagePlateau* plateau;

    /**
     * \brief L'affichage des détails
     */
    AffichageDetails* details;

public:
    /**
     * \brief Les différents éléments de la scène
     */
    enum Elements {
        Menu, //!< Le bouton de menu
        Plateau, //!< L'affichage du plateau
        Droite, //!< Le bouton pour déplacer le plateau à droite
        Gauche, //!< Le bouton pour déplacer le plateau à gauche
        Haut, //!< Le bouton pour déplacer le plateau en haut
        Bas, //!< Le bouton pour déplacer le plateau en bas
        Details, //!< L'affichage des détails
        Construction, //!< L'affichage des batiments ou vaisseaux constructibles
        Case //!< L'id générique pour l'affichage des cases
    };

    /**
     * \brief Constructeur
     *
     * \param jeu le jeu actuel
     */
    SceneJeu(Jeu& jeu);

    /**
     * \brief Destructeur
     */
    virtual ~SceneJeu();

    // Héritée de Scene
    void surMessage(Message message);
};

#endif /* SCENEJEU_HPP */
