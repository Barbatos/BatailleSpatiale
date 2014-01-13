#ifndef POSITION_HPP
#define POSITION_HPP

/**
 * \brief Cette classe défini une position dans un repère 2D
 *
 * Les attributs x et y sont public pour permettre une modification
 * et un accès plus simple
 */
class Position {
public:
    /**
     * \brief Constructeur par défaut
     *
     * \param _x la position en x
     * \param _y la position en y
     */
    Position(int _x=0, int _y=0);
    int x;///< La position en x
    int y;///< La position en y
    /**
     * \brief retourne si la position actuelle est egale a la position p
     *
     * \param p la position à comparer
     * \return egalité entre position actuelle et position p
     */
    bool operator==(Position& p);
    /**
     * \brief ajoute a la position actuelle une seconde position
     *
     * \param p la position à ajouter
     */
    void operator+=(Position& p);
    /**
     * \brief soustrait a la position actuelle une seconde position
     *
     * \param p la position à soustraire
     */
    void operator-=(Position& p);

    friend Position operator+(Position& p1, Position& p2);
    friend Position operator-(Position& p1, Position& p2);
};

Position operator+(Position& p1, Position& p2);
Position operator-(Position& p1, Position& p2);

#endif // POSITION_HPP
