/*
 * GestionnaireSons.hpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#ifndef GESTIONNAIRESONS_HPP_
#define GESTIONNAIRESONS_HPP_

#include <SFML/System/Clock.hpp>
#include <client/ressources/Ressources.hpp>

/**
 *\brief classe qui gère les différents sons qui seront joués dans l'application
 */
class GestionnaireSons {
private:

    /**
     * \brief l'horloge générale du jeu
     */
    sf::Clock* horloge;

    /**
     * \brief les ressources du jeu
     */
    Ressources& ressources;

    /**
     * \brief la musique courramment jouée
     */
    Ressources::MusicPtr musique;

public:

    /**
     * \brief Constructeur de l'objet
     * \param ressources les ressources du jeu vidéo
     */
    GestionnaireSons(Ressources& ressources);

    /**
     * \brief Destructeur de l'objet
     */
    virtual ~GestionnaireSons();
};

#endif /* GESTIONNAIRESONS_HPP_ */
