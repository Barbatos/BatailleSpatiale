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
    Position(int _x = 0, int _y = 0);
    int x; ///< La position en x
    int y; ///< La position en y

    /**
     * \brief Retourne si la position actuelle est egale a la position p
     *
     * \param p La position à comparer
     * \return Egalité entre position actuelle et position p
     */
    bool operator==(Position p) const;

    /**
     * \brief Retourne si la position actuelle est NULL
     *
     * \return Vrai si la position est NULL
     */
    bool isNull() const;

    /**
     * \brief Ajoute a la position actuelle une seconde position
     *
     * \param p La position à ajouter
     */
    void operator+=(Position& p);

    /**
     * \brief Soustrait a la position actuelle une seconde position
     *
     * \param p La position à soustraire
     */
    void operator-=(Position& p);

    /**
     * \brief Affecte les attributs d'une autre position à cette position
     *
     * \param p La position à soustraire
     */
    void operator=(Position p);

    /**
     * \brief Affecte un nouveau x et un nouveau y a la position
     *
     * \param _x Le nouveau x
     * \param _y Le nouveau y
     */
    void set(int _x, int _y);

    /**
     * \brief Met la position a NULL
     */
    void setNull();

    friend Position operator+(Position& p1, Position& p2);
    friend Position operator-(Position& p1, Position& p2);
    friend sf::Packet& operator >>(sf::Packet& paquet, Position& position);
    friend sf::Packet& operator <<(sf::Packet& paquet, const Position& position);
};

sf::Packet& operator <<(sf::Packet& paquet, const Position& position);
sf::Packet& operator >>(sf::Packet& paquet, Position& position);

Position operator+(Position& p1, Position& p2);
Position operator-(Position& p1, Position& p2);

#endif // POSITION_HPP
