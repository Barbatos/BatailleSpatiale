/*
 * Log.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef LOG_HPP
#define LOG_HPP

// Includes de la stdlib
#include <string>
#include <fstream>
#include <memory>

// Typedefs
typedef std::unique_ptr<std::ofstream> OutputStreamPtr;

/**
 * \brief Gère le fichier de log
 */
class Log {
private:
	/** \brief Fichier de log
	 *
	 * Fichier où sera enregistré tout le log, ajouté à la suite du contenu du fichier
	 */
	OutputStreamPtr fichier;

	/**
	 * \brief Constructeur
	 *
	 * Construit une nouvelle instance d'un fichier de log
	 */
	Log();

	/**
	 * \brief Unique instance du Log
	 *
	 * Seule et unique instance de la classe Log
	 */
	static Log instance;

public:
	/**
	 * \brief Destructeur
	 *
	 * Détruit l'instance du fichier de log
	 */
	virtual ~Log();

	/**
	 * \brief Récupère l'instance du fichier de log
	 *
	 * Renvoie la seule instance existante du fichier de log
	 *
	 * @return l'instance du fichier de log
	 */
	static Log& lireInstance();

	/**
	 * \brief Ajoute une ligne au fichier de log
	 *
	 * Ajoute la ligne passée en paramètre au fichier de log
	 *
	 * \param ligne la ligne à ajouter
	 */
	void ajouterLigne(std::string ligne);

	/**
	 * \class Log
	 *
	 * Classe utilisant le pattern Singleton, ce qui veut dire qu'il n'existe
	 * qu'une seule et unique instance de cette classe, initialisée au démarrage de l'application
	 * et détruite à la fermeture.
	 *
	 * Sauvegarde du texte dans un fichier de log présent à côté du fichier exécutable.
	 *
	 * Exemple d'utilisation :
	 *
	 \code
	 // On fait une action et on veut la sauvegarder
	 fichierLog.ajouterLigne("J'ai fait une action !");

	 // Note : fichierLog est un raccourci appellant la fonction Log::lireInstance()
	 \endcode
	 */
};

#define fichierLog Log::lireInstance()

#endif /* LOG_HPP_ */
