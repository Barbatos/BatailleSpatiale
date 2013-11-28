/**
 * \class Plateau Plateau.hpp "Plateau.hpp"
 *
 * \date 11/11/2013 Création
 * \author Soinou
 */

#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "DetailBatiment.hpp"
#include "DetailVaisseau.hpp"
#include "DetailEvenement.hpp"
#include "../../commun/utile/Position.hpp"

class Plateau {
private:
    sf::Int16 xVaisseau;
    sf::Int16 yVaisseau;

public:
    Plateau();
    virtual ~Plateau();

    /**
     * \brief Informe si la cellule a la position p possède un évènement
     *
     * \param p La position
     * \return vrai si elle possède un évènement
     */
    bool possedeEvenement(Position p);

    /**
     * \brief Informe si la cellule a la position p possède un vaisseau
     *
     * \param p La position
     * \return vrai si elle possède un vaisseau
     */
    bool possedeVaisseau(Position p);

    /**
     * \brief Informe si la cellule a la position p possède un batiment
     *
     * \param p La position
     * \return vrai si elle possède un batiment
     */
    bool possedeBatiment(Position p);

    /**
     * \brief Getter vaisseau
     *
     * \param p La position
     * \return Les détails du vaisseau
     */
    DetailVaisseau getVaisseau(Position p);

    /**
     * \brief Getter batiment
     *
     * \param p La position
     * \return Les détails du batiment
     */
    DetailBatiment getBatiment(Position p);

    /**
     * \brief Getter évènement
     *
     * \param p La position
     * \return Les détails de l'évènement
     */
    DetailEvenement getEvenement(Position p);

    sf::Int16 getTailleX();
    sf::Int16 getTailleY();

    void deplacerVaisseau(Position ancienne, Position nouvelle);
};

#endif /* PLATEAU_HPP */
