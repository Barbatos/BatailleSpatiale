/*
 * Controleur.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef CONTROLEUR_HPP
#define CONTROLEUR_HPP

// Pré-Déclaration de la classe Modèle
class Plateau;

#include <commun/utile/Position.hpp>

/**
 * \brief Fait le lien entre le modèle et la vue
 */
class Controleur {
    private:
        /**
         * \brief Référence vers le modèle actuel
         */
        Plateau& modele;

    public:
        /**
         * \brief Constructeur
         *
         * Instancie un nouveau Contrôleur avec le modèle passé en paramètre
         *
         * \param modele le modèle à lier
         */
        Controleur(Plateau& modele);

        /**
         * \brief Destructeur
         *
         * Détruit l'instance précédemment créée du Contrôleur
         */
        virtual ~Controleur();

        /**
         * @brief Tente d'éxécuter une action entre l'ancienne position et la nouvelle position
         *
         * L'action peut être un déplacement, une attaque,
         * une construction, ou diverses autres choses
         *
         * @param ancien l'ancienne position
         * @param nouveau la nouvelle position
         */
        void action(Position ancien, Position nouveau);
};

#endif /* CONTROLEUR_HPP */
