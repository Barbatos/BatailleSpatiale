#ifndef CELLULESERVEUR_HPP
#define CELLULESERVEUR_HPP
#include "../../commun/enum/TypeCellule.hpp"
#include "evenement/EvenementServeur.hpp"
#include "../../commun/enum/TypeBatiment.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"
#include "../structures/Structure.hpp"

/**
 * Cette classe est une case elementaire du plateau
 */
class CelluleServeur {

public:
    CelluleServeur(EvenementServeurPtr _evenement = 0, TypeCellule _type = TypeCellule::Vide);
    TypeCellule getType() const;

    bool possedeEvenement() const;
    bool possedeBatiment() const;
    bool possedeVaisseau() const;

    /**
     * \brief Indique si la cellule est disponible au deplacement
     * Si un vaisseau ou un batiment est present, alors elle retourne faux.
     * De même si un evenement est present alors on indique s'il est accessible
     *
     * \return Si accessible ou non
     */
    bool possedeEmplacement(TypeCellule _type) const;

    /**
     * \brief Indique le type de la cellule
     * Si un vaisseau ou un batiment est present, alors elle retourne un type correspondant.
     * De même si un evenement est present.
     *
     * \return Le type de la cellule.
     */
    TypeCellule statutEmplacement() const;

    /**
     * \brief Setter type
     * Modifie le type de la cellule
     *
     * \param _type le nouveau type
     */
    void setType(TypeCellule _type);

    /**
     * \brief Retourne le cout de déplacement dans la cellule
     * Si un vaisseau veut passer a travers cette cellule quel est
     * le facteur du cout de deplacement ici?
     *
     *  \return Le cout de deplacement
     */
    int getCoutDeplacement() const;

    //void subir(Structure const& attaquant);

    /**
     * \brief Indique la structure de la cellule
     *
     * \return La structure de la cellule.
     */
    Structure getAttaquant();

    /**
     * \brief Indique le type de batiment de la cellule s'il existe.
     * Si un batiment est present, alors elle retourne le type correspondant.
     *
     * \return Le type de batiment de la cellule.
     */
    TypeBatiment typeBatiment() const;

    /**
     * \brief Indique si la cellule est accessible
     * S'il n'ya ni vaisseau ni batiment, la cellule est accesible
     * S'il y a un evenement, il peut laisser la cellule accesible
     *
     * \return True pour accessible, False sinon.
     */
    bool estAccessible() const;

    BatimentServeurPtr getBatiment() const;

    EvenementServeurPtr getEvenement() const;

    void retirerVaisseau();
    VaisseauServeurPtr getVaisseau() const;
    VaisseauServeurPtr& getVaisseauPtr();
    void echangerVaisseau(CelluleServeur& cellule);
    void setVaisseau(VaisseauServeurPtr _vaisseau);

    /**
     * \brief Indique la distance maximale du vaisseau sur la cellule.
     * S'il n'y a pas de vaisseau, alors on retourne 0.
     *
     * \return La distance maximale du vaisseau sur la cellule.
     */
    int distanceMaximale(sf::Int32 energie) const;

    /**
     * \brief Indique le rayon maximale d'attaque de la cellule
     * Correspond au rayon d'attaque du vaisseau ou du batiment présent
     * (0 si aucun vaisseau ni batiment ou si le batiment ne peut attaquer)
     *
     * \return Le rayon d'attaque de la cellule.
     */
    int attaqueMaximale() const;

    //Multiple fonctions de test
    void creerVaisseauTest(TypeVaisseau type = TypeVaisseau::Chasseur);
    void creerVaisseauConstructeurTest();

    void creerBatimentEnergieTest();
    void creerBatimentBase();

    /**
     * \brief Retourne l'id du joueur sur la cellule
     *
     * Si il y a un batiment ou un vaisseau on retourne l'id
     * du propriétaire (-1) sinon
     *
     * \return L'id du joueur
     */
    sf::Int32 getIdJoueur();

    /**
     * \brief Attaque une cellule cible.
     * Les degats sont calculés selon :
     * - une base qui provient de la structure attaquante sur la cellule.
     * - un coefficient multiplicateur par l'evement, s'il existe.
     * - un coefficient en fonction du type d'attaque par rapport à la cible.
     * Ensuite, on appelle defendre qui va faire les modifications sur les parametres de la cible.
     *
     * \return la vie du vaisseau
     * \param cCible La cellule qui va etre attaqué
     */
    int attaquer(CelluleServeur *cCible);

    /**
     * \brief Inflige les degats a la structure de la cellule.
     * Les degats sont calculés selon :
     * - une base qui provient de la cellule attaquante.
     * - un coefficient multiplicateur par l'evement, s'il existe.
     *
     * \return la vie du vaisseau
     * \param degat Les degats que doit subir la cellule
     */
    int defendre(int degat);

private:
    /// L'evenement sur la cellule
    EvenementServeurPtr evenement;
    /// Le batiment sur la cellule
    BatimentServeurPtr batiment;
    /// Le vaisseau sur la cellule
    VaisseauServeurPtr vaisseau;
    /// Le type de la cellule
    TypeCellule type;

};

sf::Packet& operator <<(sf::Packet& paquet, const CelluleServeur& cellule);

#endif // CELLULESERVEUR_HPP
