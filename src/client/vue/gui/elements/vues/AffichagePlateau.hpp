/*
 * AffichagePlateau.hpp
 *
 *  Created on: 12 oct. 2013
 *      Author: Soinou
 */

#ifndef AFFICHAGEPLATEAU_HPP
#define AFFICHAGEPLATEAU_HPP

// Includes de la libstd
#include <vector>
#include <memory>

// Includes de nos classes
#include "VuesPack.hpp"

// Pré-déclarations
class AffichageDetails;
class AffichageCase;
class Etat;

/**
 * \brief Affiche le plateau dans son intégralité
 *
 * Gère l'affichage des cases, du vaisseau selectionné, etc
 * Bref, de plus ou moins toute l'interface de la scène jeu
 *
 * \see SceneJeu
 * \see ElementSouris
 */
class AffichagePlateau : public Element, public ObservateurSouris, public ObservateurClavier {
    private:

    /**
     * \brief Pointeur vers l'affichage des détails
     */
    AffichageDetails* details;

    /**
     * \brief Les cases affichées
     *
     * \see AffichageCase
     */
    std::vector<AffichageCase*> cases;

    /**
     * \brief La vue du plateau
     */
    sf::View vuePlateau;

    /**
     * \brief Etat de selection de case
     */
    Etat* etat;

    public:
    /**
     * \brief Version unique_ptr du plateau
     */
    typedef std::unique_ptr<AffichagePlateau> Ptr;

    /**
     * \brief Constructeur
     *
     * Créé un nouvel affichage plateau
     *
     * \param gui le gui contenant le plateau
     * \param id l'id du plateau
     * \param x la position en x du plateau
     * \param y la position en y du plateau
     * \param largeur la largeur du plateau
     * \param hauteur la hauteur du plateau
     * \param details l'affichage des détails
     */
    AffichagePlateau(Gui* gui, int id, int x, int y, int largeur, int hauteur,
                     AffichageDetails* details);

    /**
     * \brief Destructeur
     *
     * Détruit l'instance précédemment créée d'affichage plateau
     */
    virtual ~AffichagePlateau();

    /**
     * \brief Initialise les cases
     */
    void initialiserCases();

    /**
     * \brief Déplace la vue plateau
     *
     * \param x nombre de pixels à déplacer en x
     * \param y nombre de pixels à déplacer en y
     */
    void bougerPlateau(float x, float y);

    /**
     * \brief Appellée lors de l'appui d'une case, avec le message correspondant
     */
    void appuiCase(Message::MessageCellule message);

    // Héritées d'ElementSouris
    void clicSouris(bool clicDroit);
    void pressionSouris(sf::Mouse::Button bouton);
    void relachementSouris(sf::Mouse::Button bouton);
    void entreeSouris(sf::Vector2f position);
    void sortieSouris(sf::Vector2f position);
    void moletteSouris(int delta);

    // Héritées d'ElementClavier
    void pressionTouche(sf::Keyboard::Key touche);
    void relachementTouche(sf::Keyboard::Key touche);
    void entreeTexte(sf::Uint32 texte);

    // Héritées d'Element
    void actualiser(float delta);
    void afficher(sf::RenderWindow& affichage);
    bool contient(sf::Vector2i position);
};

#endif /* AFFICHAGEPLATEAU_HPP */
