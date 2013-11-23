#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include <vector>
#include <list>
#include "Cellule.hpp"
#include "../joueurs/Joueur.hpp"
#include "../../commun/utile/Position.hpp"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/**
 * \brief Le plateau coté serveur
 *
 */
class Plateau {

public:
    /**
     * \brief Constructeur du plateau
     *
     * \param _tailleX Taille du plateau en X
     * \param _tailleY Taille du plateau en Y
     */
    Plateau(sf::Int16 _tailleX, sf::Int16 _tailleY);
    
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
    VaisseauPtr getVaisseau(Position p);
    
    /**
     * \brief Getter batiment
     * 
     * \param p La position
     * \return Les détails du batiment
     */
    BatimentPtr getBatiment(Position p);
    
    /**
     * \brief Getter évènement
     * 
     * \param p La position
     * \return Les détails de l'évènement
     */
    EvenementPtr getEvenement(Position p);

    /**
     * \brief Getter tailleX
     * 
     * \return la taille du plateau à l'horizontal
     */
    sf::Int16 getTailleX();
    
    /**
     * \brief Getter tailleY
     * 
     * \return la taille du plateau à la verticale
     */
    sf::Int16 getTailleY();

private:
    /// Les cellules du plateau
    std::vector<std::vector<Cellule>> cellule;
    /// La taille du plateau à l'horizontal
    sf::Int16 tailleX;
    /// La taille du plateau à la verticale
    sf::Int16 tailleY;
};

#endif // PLATEAU_HPP
