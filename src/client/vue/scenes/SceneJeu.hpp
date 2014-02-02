/*
 * SceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#ifndef SCENEJEU_HPP
#define SCENEJEU_HPP

#include "ScenesPack.hpp"

#include <commun/utile/Position.hpp>

// Pré-déclarations
class AffichageCase;
class AffichageDetails;
class Bouton;
class CaseACocher;

/**
 * \brief Scène en jeu
 *
 * Scène affichant le plateau
 */
class SceneJeu : public Scene, public ObservateurSouris {
    private:

        /**
         * \brief Liste des cases du plateau
         */
        std::list<AffichageCase*> cases;

        /**
         * \brief L'affichage des détails
         */
        AffichageDetails* details;

        /**
         * \brief Bouton de déplacement (Déplacer vaisseau)
         */
        Bouton* deplacement;

        /**
         * \brief Bouton d'attaque
         */
        Bouton* attaque;

        /**
         * \brief Case concernant la portée de deplacement
         */
        CaseACocher* porteeDeplacement;

        /**
         * \brief Case concernant la portée d'attaque
         */
        CaseACocher* porteeAttaque;

        /**
         * \brief case concernant la portée de construction
         */
        CaseACocher* porteeConstruction;

        /**
         * \brief La vue du plateau
         */
        sf::View vue;

        /**
         * \brief La destination choisie par le clic droit du joueur
         */
        Position destination;

    public:
        /**
         * \brief Les différents éléments de la scène
         */
        enum Elements {
            Deplacement, //!< Le bouton d'action
            PorteeAttaque, //!< La case qui affiche la portée d'attaque
            PorteeDeplacement, //!< La case qui affiche la portée de déplacement
            PorteeConstruction, //!< La case qui affiche la portée de construction
            Attaque, //!< Le bouton d'attaque
            Menu, //!< Le bouton de menu
            Droite, //!< Le bouton pour déplacer le plateau à droite
            Gauche, //!< Le bouton pour déplacer le plateau à gauche
            Haut, //!< Le bouton pour déplacer le plateau en haut
            Bas, //!< Le bouton pour déplacer le plateau en bas
            Details, //!< L'affichage des détails
            Construction, //!< L'affichage des bâtiments ou vaisseaux constructible
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

        /**
         * \brief Initialise l'affichage du plateau
         */
        void initialiserPlateau();

        /**
         * \brief Retourne si la cellule donnée est valide ou non pour être une destination
         *
         * \param cellule la cellule à tester
         * \return si elle est valide ou non
         */
        bool valide(Cellule cellule);

        /**
         * \brief Appelée lors de l'appui d'une case
         *
         * \param message le message lié à la case appuyée
         */
        void appuiCase(Message::MessageCellule message);

        /**
         * \brief Tente d'effectuer une action
         */
        void effectuerAction();

        // Héritée de Scene
        void surMessage(Message message);

        // Héritées de ObservateurSouris
        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);
};

#endif /* SCENEJEU_HPP */
