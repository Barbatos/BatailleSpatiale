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
        /// Constructeur par défaut
        Position(int _x=0, int _y=0);
        int x;
        int y;
};

#endif // POSITION_HPP
