#ifndef PLATEAUSERVEUR_HPP
#define PLATEAUSERVEUR_HPP
#include <vector>
#include <list>
#include "CelluleServeur.hpp"
#include "NoeudServeur.hpp"
#include "../joueurs/JoueurServeur.hpp"
#include "../../commun/utile/Position.hpp"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/**
 * \brief Le plateau coté serveur
 *
 */
class PlateauServeur {

public:
    /**
     * \brief Constructeur du plateau
     *
     * \param _tailleX Taille du plateau en X
     * \param _tailleY Taille du plateau en Y
     */
    PlateauServeur(sf::Int16 _tailleX, sf::Int16 _tailleY);

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
    VaisseauServeurPtr getVaisseau(Position p);

    /**
     * \brief Getter batiment
     *
     * \param p La position
     * \return Les détails du batiment
     */
    BatimentServeurPtr getBatiment(Position p);

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
    std::list<NoeudServeur> getZoneParcourable(Position positionVaisseau);

    /**
     * \brief Retourne le chemin jusqu'à la position p
     *
     * \param p La position à atteindre
     * \param zoneParcourable la zone recherché par le pathfinding
     * \return Le chemin à effectuer de la première à la dernière case
     */
    static std::list<Position> obtenirChemin(Position p, std::list<NoeudServeur>* zoneParcourable);

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
    
    /**
     * \brief Setter listeJoueur
     * 
     * \param joueurs référence vers la liste des joueurs
     */
    void setJoueurs(std::vector<JoueurServeur> *_joueurs);
    
    PlateauServeur& operator=(const PlateauServeur& plateau2);

private:
    /// Liste des joueurs
    std::vector<JoueurServeur> *joueurs;
    /// Les cellules du plateau
    std::vector<std::vector<CelluleServeur>> cellule;
    /// La taille du plateau à l'horizontal
    sf::Int16 tailleX;
    /// La taille du plateau à la verticale
    sf::Int16 tailleY;

    friend sf::Packet& operator <<(sf::Packet& paquet, const PlateauServeur& plateau);
};

sf::Packet& operator <<(sf::Packet& paquet, const PlateauServeur& plateau);

typedef std::shared_ptr<PlateauServeur> PlateauServeurPtr;

#endif // PLATEAUSERVEUR_HPP
