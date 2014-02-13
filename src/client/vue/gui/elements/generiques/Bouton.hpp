/*
 * Bouton.hpp
 *
 * >>>> Ne pas formater svp :( <<<<
 *
 *  Created on: 5 oct. 2013
 *      Author: Tendry
 */

#ifndef BOUTON_HPP
#define BOUTON_HPP

// Includes de nos classes
#include "GeneriquesPack.hpp"
#include "Label.hpp"

// Pré-déclarations
class Affichage;

/**
 * \brief Représente un bouton, qu'on peut cliquer pour effectuer une action
 *
 * \see Element, ObservateurSouris
 */
class Bouton : public Element, public ObservateurSouris {
    private:
        /**
         * \brief Un label
         *
         * Le label présent sur le bouton
         */
        Label label;

        /**
         * \brief L'image normale du bouton
         *
         * L'image du bouton lorsqu'il ne se passe rien
         */
        sf::Sprite normal;

        /**
         * \brief L'image du bouton au survol
         *
         * L'image du bouton lorsqu'il est survolé
         */
        sf::Sprite survol;

        /**
         * \brief L'image du bouton à l'appui
         *
         * L'image du bouton lorsqu'il est appuyé
         */
        sf::Sprite appui;

    public:
        /**
         * \brief Constructeur
         *
         * Créé un nouveau bouton avec les paramètres donnés
         *
         * \param gui le gui contenant le bouton
         * \param id l'id du bouton
         * \param texte le texte du bouton
         * \param x sa position en x
         * \param y sa position en y
         * \param largeur sa largeur
         * \param hauteur sa hauteur
         */
        Bouton(Gui* gui, int id, std::string texte, float x, float y, float largeur, float hauteur);

        /**
         * \brief Destructeur
         *
         * Détruit un bouton précédemment créé
         */
        virtual ~Bouton();

        /**
         * \brief Retourne le texte du bouton
         *
         * \return le texte du bouton
         */
        std::string lireTexte();

        /**
         * \brief Version wstring de ecrireTexte(std::string)
         *
         * \param texte le nouveau texte du bouton
         */
        void ecrireTexte(std::wstring texte);

        /**
         * \brief Change le texte du bouton
         *
         * \param texte le nouveau texte du bouton
         */
        void ecrireTexte(std::string texte);

        // Héritées de ElementSouris
        void actualiser(float delta);
        void afficher();
        bool contient(sf::Vector2i position);

        // Héritées d'ObservateurSouris
        void clicSouris(bool clicDroit);
        void pressionSouris(sf::Mouse::Button bouton);
        void relachementSouris(sf::Mouse::Button bouton);
        void entreeSouris(sf::Vector2f position);
        void sortieSouris(sf::Vector2f position);
        void moletteSouris(int delta);

        /**
         * \class Bouton
         *
         * Bouton simple, qu'on peut cliquer pour effectuer une action
         *
         * Exemple d'utilisation :
         *
         \code
         // Dans le constructeur d'une scène :
         // Ajout d'un bouton à l'objet 'gui' de type Gui préablement défini,
         // avec l'id 0, possédant le texte "Je suis un bouton", en position
         // 50x/50y, faisant 200 par 20 pixels

         new Bouton(&gui, 0, "Je suis un bouton !", 50, 50, 200, 20);

         // Dans la fonction surMessage() de la même scène :
         switch(id)
         {
         case 0:
         // La souris a cliqué sur notre bouton
         faireQuelqueChose();
         break;
         default:
         break;
         }
         \endcode
         *
         * \see Scene
         */
};

#endif /* BOUTON_HPP */
