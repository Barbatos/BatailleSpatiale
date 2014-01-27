/*
 * Gui.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef GUI_HPP
#define GUI_HPP

// Includes de la stdlib
#include <queue>
#include <memory>
#include <list>

// Includes de la SFML
#include <SFML/Window/Event.hpp>

// Includes de nos classes
#include "Element.hpp"
#include "evenements/ObservateurSouris.hpp"
#include "evenements/ObservateurClavier.hpp"
#include "evenements/Message.hpp"

// Pré déclarations
class Scene;

/**
 * \brief Représente une interface, contenant des éléments graphiques
 *
 * Contient tout les élements affichés à l'écran, et intéragit avec eux
 */
class Gui {
    private:
        /**
         * \brief La liste des éléments présents dans ce gui
         */
        std::list<Element::Ptr> elements;

        /**
         * \brief La liste des observateurs souris
         */
        std::list<ObservateurSouris*> observateursSouris;

        /**
         * \brief La liste des observateurs clavier
         */
        std::list<ObservateurClavier*> observateursClavier;

        /**
         * \brief La file des messages envoyés dans ce gui
         */
        std::queue<Message> messages;

        /**
         * \brief L'horloge interne utilisée pour la méthode d'actualisation
         */
        sf::Clock horloge;

        /**
         * \brief La fenêtre où est dessiné le gui
         */
        sf::RenderWindow* fenetre;

        /**
         * \brief La scène où est dessiné le gui
         */
        Scene* scene;

    public:
        /**
         * \brief Version shared_ptr du gui
         */
        typedef std::shared_ptr<Gui> Ptr;

        /**
         * \brief Constructeur
         *
         * \param fenetre la fenêtre où sera dessiné le gui
         * \param scene la scène où sera dessiné le gui
         */
        Gui(sf::RenderWindow* fenetre, Scene* scene);

        /**
         * \brief Destructeur
         */
        virtual ~Gui();

        /**
         * \brief Retourne la scène où est dessiné le gui
         *
         * \return la scène où est dessiné le gui
         */
        Scene* lireScene();

        /**
         * \brief Ajoute l'élément donné au gui
         *
         * \param element l'élement à ajouter
         */
        void ajouter(Element::Ptr element);

        /**
         * \brief Ajoute l'élement donné au gui
         *
         * Version pointeur simple de l'ajout
         *
         * Appelle ajouter(Element::Ptr) avec l'élement passé sous forme d'un Element::Ptr
         *
         * \param element l'élement à ajouter
         */
        void ajouter(Element* element);

        /**
         * \brief Ajoute l'observateur souris donné au gui
         *
         * \param observateur l'observateur souris à ajouter
         */
        void ajouterObservateurSouris(ObservateurSouris* observateur);

        /**
         * \brief Ajoute l'observateur clavier donné au gui
         *
         * \param observateur l'observateur à ajouter
         */
        void ajouterObservateurClavier(ObservateurClavier* observateur);

        /**
         * \brief Ajoute le message à la file de message du gui
         *
         * \param message le message généré
         */
        void ajouterMessage(Message message);

        /**
         * \brief Traite l'évènement donné
         *
         * \param evenement l'évènement à traiter
         */
        void traiter(sf::Event evenement);

        /**
         *
         * @param evenement
         */
        void envoyerPressionBoutonSouris(sf::Event::MouseButtonEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerMouvementSouris(sf::Event::MouseMoveEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerMoletteSouris(sf::Event::MouseWheelEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerPressionToucheClavier(sf::Event::KeyEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerRelachementToucheClavier(sf::Event::KeyEvent evenement);

        /**
         *
         * @param evenement
         */
        void envoyerTexteClavier(sf::Event::TextEvent evenement);

        /**
         * \brief Actualise le gui
         */
        void actualiser();

        /**
         * \brief Affiche le gui
         */
        void afficher();

        /**
         * \brief Récupère le dernier message de la file de messages du gui
         *
         * Place le dernier message de la file dans le pointeur passé en paramètre,
         * et renvoie true si il reste des messages, et false si il n'en reste pas
         *
         * \param message pointeur vers l'objet où placer le message
         * \return true si il reste des messages, false sinon
         */
        bool obtenirMessage(Message* message);
};

#endif /* GUI_HPP */
