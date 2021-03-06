/*
 * Utile.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef UTILE_HPP
#define UTILE_HPP

// Includes de la libstd
#include <global.hpp>

// Includes de la SFML
#include <SFML/Graphics.hpp>

// Includes des enums/structs du modèle
#include <enums.hpp>
#include <structs.hpp>

// Includes des classes utiles
#include <commun/utile/Position.hpp>

/**
 * \brief Boîte à outils
 *
 * Contient de nombreuses fonctions utiles
 */
namespace Utile {
    using namespace std;

    /**
     * \brief Génère une erreur
     *
     * Permet d'afficher l'erreur donnée en paramètre et de quitter le programme immédiatement
     *
     * \param endroit l'endroit où s'est passée l'erreur
     * \param erreur simple message décrivant l'erreur
     */
    void erreur(string endroit, string erreur);

    /**
     * \brief Donne le nom du fichier à partir d'un chemin
     *
     * Permet de trouver le nom du fichier à partir d'un chemin, et de le renvoyer.
     *
     * Exemple : C:/exemple/de/chemin/exemple/de/fichier.cpp -> fichier.cpp
     *
     * \param cheminFichier le chemin à tester
     * \return le nom du fichier contenu dans le chemin
     */
    string nomFichier(const string& cheminFichier);

    /**
     * \brief Donne l'extension du fichier à partir d'un chemin/nom
     *
     * Permet de trouver l'extension à partir d'un chemin ou d'un nom de fichier, et de le renvoyer.
     *
     * Exemple : nomDeFichier.extension -> extension
     *
     * \param cheminFichier le chemin ou le nom du fichier
     * \return l'extension du fichier donné
     */
    string extension(const string& cheminFichier);

    /**
     * \brief Renvoie la date actuelle
     *
     * Renvoie une chaîne de caractère contenant la date actuelle sous le format AAAA-MM-JJ-hh:mm:ss
     *
     * \return la date actuelle dans une chaîne de caractère
     */
    string dateActuelle();

    /**
     * \brief Redimensionne l'image donnée en paramètre
     *
     * Redimensionne l'image donnée, en gardant ou non les proportions
     *
     * \param image l'image à redimensionner
     * \param largeur la nouvelle largeur
     * \param hauteur la nouvelle hauteur
     * \param proportions si les proportions doivent être gardées ou non
     */
    void redimensionnerImage(sf::Sprite& image, float largeur, float hauteur, bool proportions);

    /**
     * \brief Retourne le type du vaisseau donné sous forme d'un std::string
     *
     * \param type le type du vaisseau
     * \return le type sous forme d'un std::string
     */
    std::wstring convertir(TypeVaisseau type);

    /**
     * \brief Retourne le type du bâtiment donné sous forme d'un std::string
     *
     * \param type le type du bâtiment
     * \return le type sous forme d'un std::string
     */
    std::wstring convertir(TypeBatiment type);

    /**
     * \brief Retourne le type d'évènement donné sous forme d'un std::string
     *
     * \param type le type de l'évènement
     * \return le type sous forme d'un std::string
     */
    std::wstring convertir(TypeEvenement type);

    std::string lireFichier(TypeVaisseau type, int id);

    /**
     * \brief Retourne le chemin vers l'image correspondant au vaisseau donné
     *
     * \param details le vaisseau
     * \return l'image associée
     */
    std::string lireFichier(DetailVaisseau details);

    std::string lireFichier(TypeBatiment type, int id);

    /**
     * \brief Retourne le chemin vers l'image correspondant au bâtiment donné
     *
     * \param details le bâtiment
     * \return l'image associée
     */
    std::string lireFichier(DetailBatiment details);

    /**
     * \brief Retourne le chemin vers l'image correspondant à l'évènement donné
     *
     * \param details l'évènement
     * \return l'image associée
     */
    std::string lireFichier(DetailEvenement details);

    /**
     * \brief Retourne les détails donnés sous forme d'un string
     *
     * \param details les détails à transformer
     */
    std::wstring toString(DetailBatiment details);

    /**
    * \brief Retourne les détails donnés sous forme d'un string
    *
    * \param details les détails à transformer
    */
    std::wstring toString(DetailVaisseau details);

    /**
    * \brief Retourne les détails donnés sous forme d'un string
    *
    * \param details les détails à transformer
    */
    std::wstring toString(DetailEvenement details);

    /**
    * \brief Retourne la position donnée sous forme d'un string
    *
    * \param position la position à transformer
    */
    std::wstring toString(Position position);
}

#endif /* UTILE_HPP */
