/*
 * Archive.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <string>
#include <vector>

/**
 * \brief Permet d'accéder aux ressources depuis un fichier toc
 *
 * Lit un fichier toc et accède aux ressources présentes dans ce fichier toc
 * \todo Permettre la lecture depuis un fichier .zip
 * \todo Ajouter toutes les extensions
 */
class Archive {
private:
	/** \brief Liste d'images
	 *
	 * Liste des images présentes dans le fichier.toc lu
	 */
	std::vector<std::string> images;

	/** \brief Liste de polices
	 *
	 * Voir #images
	 */
	std::vector<std::string> polices;

	/** \brief Liste de sons
	 *
	 * Voir #images
	 */
	std::vector<std::string> sons;

	/** \brief Liste de musiques
	 *
	 * Voir #images
	 */
	std::vector<std::string> musiques;

	/** \brief Lit le fichier toc donné
	 *
	 * Lit le fichier .toc donné en paramètre et ajoute tout son contenu
	 * dans la liste de fichiers donnée en paramètre
	 *
	 * \param cheminToc le chemin vers le fichier de ressources
	 * \param fichiers le tableau où stocker les fichiers
	 */
	void lireToc(const std::string cheminToc,
	             std::vector<std::string>& fichiers);

	/** \brief Trie le fichier donné
	 *
	 * Met le fichier donné dans la liste correspondante selon son extension
	 * Exemple : .png -> images; .wav -> sons; .mp3 -> musiques
	 *
	 * \param fichier le fichier à trier
	 */
	void trierFichier(std::string fichier);

public:
	/**
	 * \brief Constructeur
	 *
	 * Construit une nouvelle Archive à partir du fichier donné
	 *
	 * \param fichier le chemin vers le fichier toc
	 */
	Archive(std::string fichier);

	/**
	 * \brief Destructeur
	 *
	 * Détruit une instance précédemment créée d'une Archive
	 */
	virtual ~Archive();

	/** \brief Récupère les images de l'archive
	 *
	 * Récupère la liste des images lues dans le fichier .toc
	 */
	std::vector<std::string> lireImages();

	/** \brief Récupère les polices de l'archive
	 *
	 * Voir lireImages()
	 */
	std::vector<std::string> lirePolices();

	/** \brief Récupère les sons de l'archive
	 *
	 * Voir lireImages()
	 */
	std::vector<std::string> lireSons();

	/** \brief Récupère les musiques de l'archive
	 *
	 * Voir lireImages()
	 */
	std::vector<std::string> lireMusiques();

};

#endif /* ARCHIVE_HPP */
