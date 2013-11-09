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
};

#endif // POSITION_HPP
