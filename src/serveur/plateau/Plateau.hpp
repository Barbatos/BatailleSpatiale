#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include <vector>
#include <list>
#include "Cellule.hpp"
#include "../Joueur.hpp"
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
    Plateau(sf::Int32 _tailleX, sf::Int32 _tailleY);

private:
    /// Les cellules du plateau
    std::vector<std::vector<Cellule>> cellule;
};

#endif // PLATEAU_HPP
