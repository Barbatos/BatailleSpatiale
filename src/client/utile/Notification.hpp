/*
 * Notification.hpp
 *
 *  Created on: 12 févr. 2014
 *      Author: Soinou
 */

#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <string>
#include <list>

#include <SFML/Graphics.hpp>

/**
 * \brief Représente une boîte, affichant un message
 */
class Boite {
    private:
        /**
         * \brief Le cadre de la boîte
         */
        sf::RectangleShape cadre;

        /**
         * \brief Le texte de la boîte
         */
        sf::Text texte;

        /**
         * \brief Le temps d'affichage de la boîte
         */
        int tempsAffichage;

        /**
         * \brief Le temps écoulé depuis la création de la boîte
         */
        int tempsEcoule;

    public:
        /**
         * \brief Typedef pour une utilisation des listes plus simples
         */
        typedef std::list<Boite>::iterator It;

        /**
         * \brief Constructeur par défaut
         *
         * \param auteur l'auteur du message
         * \param message le message
         * \param tempsAffichage le temps d'affichage du message (millisecondes)
         */
        Boite(std::string auteur, std::string message, int tempsAffichage,
                sf::Font& police);

        /**
         * \brief Constructeur avec gestion des caractères spéciaux
         *
         * \param auteur l'auteur du message
         * \param message le message
         * \param tempsAffichage le temps d'affichage du message (millisecondes)
         */
        Boite(std::wstring auteur, std::wstring message, int tempsAffichage,
                sf::Font& police);

        /**
         * \brief Destructeur
         */
        ~Boite();

        /**
         * \brief Actualise la boîte
         *
         * \param delta le temps écoulé depuis le dernier appel
         */
        void actualiser(float delta);

        /**
         * \brief Affiche la boîte
         */
        void afficher();

        /**
         * \brief Change la position de la boîte
         *
         * \param x la position en x
         * \param y la position en y
         */
        void ecrirePosition(int x, int y);

        /**
         * \brief Retourne si la boîte a fini son affichage
         *
         * \return si la boîte a fini son affichage
         */
        bool estTermine();
};

/**
 * \brief Gère les notifications (boîtes de message)
 */
class Notification {
    private:
        /**
         * \brief Seule instance de la classe
         */
        static Notification* instance;

        /**
         * \brief La liste de boîtes
         */
        std::list<Boite> boites;

        /**
         * \brief La police utilisée par les boîtes
         */
        sf::Font police;

        /**
         * \brief Constructeur
         */
        Notification();

    public:
        /**
         * \brief Destructeur
         */
        virtual ~Notification();

        /**
         * \brief Initialise l'instance de la classe
         */
        static void initialiser();

        /**
         * \brief Détruit l'instance de la classe
         */
        static void detruire();

        /**
         * \brief Actualise les notifications
         *
         * \param delta le temps écoulé depuis le dernier appel
         */
        void actualiser(float delta);

        /**
         * \brief Affiche les notifications
         */
        void afficher();

        /**
         * \brief Retourne l'instance de la classe
         *
         * \return l'instance de la classe
         */
        static Notification& lireInstance();

        /**
         * \brief Change la police utilisée par les boîtes de la classe
         *
         * \param police la police à utiliser
         */
        void ecrirePolice(sf::Font& police);

        /**
         * \brief Ajoute un nouveau message
         *
         * \param auteur l'auteur du message
         * \param message le message
         * \param tempsAffichage le temps d'affichage du message
         */
        void ajouterMessage(std::string auteur, std::string message,
                int tempsAffichage);

        /**
         * \brief Ajoute un nouveau message avec gestion des caractères spéciaux
         *
         * \param auteur l'auteur du message
         * \param message le message
         * \param tempsAffichage le temps d'affichage du message
         */
        void ajouterMessage(std::wstring auteur, std::wstring message,
                int tempsAffichage);
};

/**
 * \brief Define pour une utilisation transparente du Singleton
 */
#define notification Notification::lireInstance()

#endif /* NOTIFICATION_HPP */
