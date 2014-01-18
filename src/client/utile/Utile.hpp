/*
 * Utile.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef UTILE_HPP
#define UTILE_HPP

// Includes de la libstd
#include <string>

// Includes de la SFML
#include <SFML/Graphics.hpp>

#include <commun/enum/TypeVaisseau.hpp>
#include <commun/enum/TypeBatiment.hpp>
#include <commun/enum/TypeEvenement.hpp>
#include <client/modele/structures/DetailBatiment.hpp>
#include <client/modele/structures/DetailVaisseau.hpp>
#include <client/modele/plateau/DetailEvenement.hpp>
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
     * @brief Retourne le type du vaisseau donné sous forme d'un std::string
     *
     * @param type le type du vaisseau
     * @return le type sous forme d'un std::string
     */
    std::string convertir(TypeVaisseau type);

    /**
     * @brief Retourne le type du bâtiment donné sous forme d'un std::string
     *
     * @param type le type du bâtiment
     * @return le type sous forme d'un std::string
     */
    std::string convertir(TypeBatiment type);

    /**
     * @brief Retourne le type d'évènement donné sous forme d'un std::string
     *
     * @param type le type de l'évènement
     * @return le type sous forme d'un std::string
     */
    std::string convertir(TypeEvenement type);

    /**
     * @brief Retourne le chemin vers l'image correspondant au vaisseau donné
     *
     * @param type le type du vaisseau
     * @return l'image associée
     */
    std::string lireFichier(TypeVaisseau type);

    /**
     * @brief Retourne le chemin vers l'image correspondant au bâtiment donné
     *
     * @param type le type du bâtiment
     * @return l'image associée
     */
    std::string lireFichier(TypeBatiment type);

    /**
     * @brief Retourne le chemin vers l'image correspondant à l'évènement donné
     *
     * @param type le type de l'évènement
     * @return l'image associée
     */
    std::string lireFichier(TypeEvenement type);

    std::string to_string(DetailBatiment details);

    std::string to_string(DetailVaisseau details);

    std::string to_string(DetailEvenement details);

    std::string to_string(Position position);
}

#endif /* UTILE_HPP */
