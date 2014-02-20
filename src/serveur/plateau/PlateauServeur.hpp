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
    PlateauServeur(sf::Int32 _tailleX, sf::Int32 _tailleY);

    /**
     * \brief Initialisation de test
     * Cette methode est juste pour faire un plateau de test qui
     * ne seras pas utilisé lors de la release
     *
     */
    void initialisationTest();

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
    EvenementServeurPtr getEvenement(Position p);

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
     * \param videTolere Le vide compte t'il comme une cellule autour?
     * \return La liste des cellules accessibles
     */
    std::list<Position> celluleAutour(Position p, bool videTolere = false);

    /**
     * \brief Retourne la zone parcourable depuis une case contenant un vaisseau
     *
     * \param positionVaisseau La position contenant le vaisseau
     * \return La zone parcourable
     */
    std::list<NoeudServeur> getZoneParcourable(Position positionVaisseau, sf::Int32 energie);

    /**
     * \brief Retourne la zone attaquable depuis une case contenant un vaisseau ou un batiment
     *
     * \param p La position de la cellule
     * \return La zone attaquable
     */
    std::list<NoeudServeur> getZoneAttaquable(Position p);

    /**
     * \brief Retourne le chemin jusqu'à la position p
     *
     * \param p La position à atteindre
     * \param zoneParcourable la zone recherché par le pathfinding
     * \return Le chemin à effectuer de la première à la dernière case
     */
    static std::list<Position> obtenirChemin(Position p, std::list<NoeudServeur> zoneParcourable);

    /**
     * \brief Getter tailleX
     *
     * \return la taille du plateau à l'horizontal
     */
    sf::Int32 getTailleX();

    /**
     * \brief Getter tailleY
     *
     * \return la taille du plateau à la verticale
     */
    sf::Int32 getTailleY();

    /**
     * \brief Setter listeJoueur
     *
     * \param joueurs référence vers la liste des joueurs
     */
    void setJoueurs(std::vector<JoueurServeur> *_joueurs);

    /**
     * \brief Permet de déplacer un vaisseau d'une position a une autre
     *
     * \param p1 Position d'une cellule
     * \param p2 Position d'une cellule
     * \return Vrai si au moins une cellule contient un vaisseau et l'autre non
     */
    bool deplacerVaisseau(Position p1, Position p2, std::list<NoeudServeur> zoneParcourable, JoueurServeur& joueur);

    /**
     * \brief copie d'un plateau
     *
     * \param plateau2 le plateau a copier
     * \return La copie du plateau
     */
    PlateauServeur& operator=(const PlateauServeur& plateau2);

    /**
     * \brief Retourne la zone construtible pour les vaisseaux du joueur
     *
     * \param idJoueur l'id du joueur
     * \return Une liste de Position où l'on peut construire des vaisseaux
     */
    std::list<Position> getZoneConstructibleVaisseau(sf::Int32 idJoueur);

    /**
     * \brief Retourne la zone construtible pour les batiments a partir d'une case
     *
     * \param idJoueur l'id du joueur
     * \param p la position du joueur
     * \return Une liste de Position où l'on peut construire des batiment
     */
    std::list<Position> getZoneConstructibleBatiment(Position position, sf::Int32 idJoueur);
    
    /**
     * \brief Retourne la zoneVisible autour d'un point
     * 
     * \param zoneVisible la zone visible deja presente + la nouvelle
     * \param p la position autour duquel on cherche la zoneVisible
     */
    void getZoneVisiblePosition (std::list<NoeudServeur>& zoneVisible, Position p);
    
    /**
     * \brief Retourne la zoneVisible d'un joueur
     * 
     * \param idJoueur le numero du joueur
     * \return Une liste de noeuds des points que peut voir le joueur
     */
    std::list<NoeudServeur> getZoneVisible (sf::Int32 idJoueur);

    int attaquer(Position attaquant, Position cible);

    void effectuerTour();
    
    

private:
    /// Liste des joueurs
    std::vector<JoueurServeur> *joueurs;
    /// Les cellules du plateau
    std::vector<std::vector<CelluleServeur>> cellule;
    /// La taille du plateau à l'horizontal
    sf::Int32 tailleX;
    /// La taille du plateau à la verticale
    sf::Int32 tailleY;

    friend class ReseauServeur;

    friend sf::Packet& operator <<(sf::Packet& paquet, const PlateauServeur& plateau);
    
    std::vector<BatimentServeur>* getListeConstruction(Position position, sf::Int32 idJoueur);
};

sf::Packet& operator <<(sf::Packet& paquet, const PlateauServeur& plateau);

typedef std::shared_ptr<PlateauServeur> PlateauServeurPtr;

#endif // PLATEAUSERVEUR_HPP
