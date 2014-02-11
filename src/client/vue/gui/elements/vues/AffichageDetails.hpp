/*
 * AffichageDetails.hpp
 *
 *  Created on: 18 oct. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGEDETAILS_HPP
#define AFFICHAGEDETAILS_HPP

// Includes de la libstd
#include <memory>

// Includes du 'pack' vues
#include "VuesPack.hpp"

// Includes de nos classes
#include <client/vue/gui/elements/generiques/Label.hpp>
#include <client/vue/gui/elements/generiques/BarreMesure.hpp>
#include <client/vue/gui/elements/generiques/BarreStatut.hpp>


// Includes du modèle
#include <commun/enum/TypeVaisseau.hpp>

/**
 * \brief Affiche les détails de la case selectionnée
 *
 * Donne les détails de la case actuellement selectionnée,
 * qu'elle possède un vaisseau, un batiment, un evenement ou rien du tout
 *
 * \see Element
 */
class AffichageDetails : public Element {
    private:
    /**
     * \brief Le fond des informations sur la case selectionnée
     */
    sf::RectangleShape fondCase;

    /**
     * \brief Le fond des informations joueurs
     */
    sf::RectangleShape fondJoueurs;

    /**
     * \brief Informations sur la case selectionnée
     *
     * Le texte donnant les informations sur la case selectionnée
     *
     * \see Label
     */
    Label infosCase;

    /**
     * \brief Informations sur les joueurs
     *
     * Le texte donnant des informations sur les joueurs
     *
     * \see Label
     */
    Label infosJoueurs;

    /**
     * \brief La position actuellemment seléctionnée
     *
     * La position actuellement choisie par le joueur
     *
     * Vaut (-1, -1) si rien n'est selectionné
     *
     * \see Position
     */
    Position position;

    /**
     * \brief la barre représentant le niveau de commandement
     */
    BarreStatut* commandementBarre;

    /**
     * \brief la barre représentant le niveau d'énergie
     */
    BarreStatut* energieBarre;

    /**
     * \brief la barre représentant le niveau de réquisition
     */
    BarreStatut* requisitionBarre;

    /**
     * \brief la barre représentant le niveau de matériaux
     */
    BarreStatut* materiauxBarre;

    /**
     * \brief représente la barre de santé pour un vaisseau
     */
    BarreMesure* santeVaisseau;

    /**
     * \brief représente la bare de santé pour un bâtiment
     */
    BarreMesure* santeBatiment;

    public:
    /**
     * \brief Version typedef des détails
     */
    typedef std::shared_ptr<AffichageDetails> Ptr;

    /**
     * \brief Constructeur
     *
     * Créé une nouvelle instance d'affichage détails
     *
     * \param gui le gui contenant les détails
     * \param id l'id des détails
     * \param x la position en x des détails
     * \param y la position en y des détails
     * \param largeur la largeur des détails
     * \param hauteur la hauteur des détails
     */
    AffichageDetails(Gui* gui, int id, float x, float y, float largeur, float hauteur);

    /**
     * \brief Destructeur
     *
     * Détruit l'instance précedemment créée d'affichage détails
     */
    virtual ~AffichageDetails();

    /**
     * \brief Retourne si une case est actuellement selectionnée
     *
     * \return si une case est selectionnée
     */
    bool estSelectionne();

    /**
     * \brief Retourne la position de la case actuellement selectionnée
     *
     * \return la position actuellement selectionnée
     */
    Position lirePosition();

    /**
     * \brief Selectionne la case donnée
     *
     * Surcharge de selectionner(Position position) et de selectionner()
     *
     * \param i la position en i de la case
     * \param j la position en j de la case
     */
    void selectionner(int i, int j);

    /**
     * \brief Selectionne la case donnée
     *
     * Surcharge de selectionner(int i, int j) et de selectionner()
     *
     * \param position la position de la case
     */
    void selectionner(Position position);

    /**
     * \brief Selectionne la case par défaut
     *
     * Selectionne la case par défaut (-1, -1), c'est à dire aucune case.
     * En clair, déselectionne l'éventuelle case selectionnée
     *
     * Surcharge de selectionner(int i, int j) et de selectionner(Position position)
     */
    void selectionner();

    // Héritées d'Element
    void actualiser(float delta);
    void afficher();
    bool contient(sf::Vector2i position);
};

#endif /* AFFICHAGEDETAILS_HPP */
