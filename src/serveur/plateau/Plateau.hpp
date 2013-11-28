#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include <vector>
#include <list>
#include "Cellule.hpp"
#include "Noeud.hpp"
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
     * \brief Retourne le cout de deplacement d'une cellule
     *
     * \param p La position de la cellule
     * \return Le cout de déplacement
     */
    int getCoutDeplacement(Position p);

    /**
     * \brief Retourne le deplacement max que peut faire un vaisseau
     *
     * \param p La position du vaisseau
     * \return Le déplacement max
     */
    int getDeplacementMax(Position p);

    /**
     * \brief Retourne si la cellule est accessible a la position p
     *
     * \param p La position de la cellule
     * \return Vrai si la cellule est accessible
     */
    bool celluleAccessible(Position p);

    /**
     * \brief Retourne les cellules accessibles autour d'une cellule
     *
     * \param p La position de la cellule
     * \return La liste des cellules accessibles
     */
    std::list<Position> celluleAutour(Position p);

    /**
     * \brief Retourne la zone parcourable depuis une case contenant un vaisseau
     *
     * \param positionVaisseau La position contenant le vaisseau
     * \return La zone parcourable
     */
    std::list<Noeud> getZoneParcourable(Position positionVaisseau);

    /**
     * \brief Retourne le chemin jusqu'à la position p
     * 
     * \param p La position à atteindre
     * \param zoneParcourable la zone recherché par le pathfinding
     * \return Le chemin à effectuer de la première à la dernière case
     */
    static std::list<Position> obtenirChemin(Position p, std::list<Noeud>* zoneParcourable);

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
