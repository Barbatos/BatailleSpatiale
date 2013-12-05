/*
 * Jeu.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */
#ifndef JEU_HPP
#define JEU_HPP

#include <client/vue/Affichage.hpp>
#include <client/modele/Plateau.hpp>
#include <client/controleur/Controleur.hpp>
#include <client/vue/Scenes.hpp>
#include <client/ressources/Ressources.hpp>
#include <commun/ReseauClient.hpp>
#include <memory>

typedef std::unique_ptr<Scene> ScenePtr;
typedef std::unique_ptr<ReseauClient> ReseauPtr;

/**
 * \brief Conteneur du jeu
 *
 * Contient tout les éléments du jeu : Modèle, Contrôleur, Vue (Scene) et Affichage, ainsi que les Ressources du jeu
 */
class Jeu
{
	private:
		/**
		 * \brief Affichage
		 *
		 * La fenêtre affichant le jeu
		 *
		 * \see Affichage
		 */
		Affichage affichage;

		/**
		 * \brief Modèle
		 *
		 * Le modèle contenant les différentes données du jeu
		 *
		 * \see Modèle
		 */
		Plateau modele;

		/**
		 * \brief Contrôleur
		 *
		 * Le contrôleur faisant le lien entre la vue et le modèle
		 *
		 * \see Contrôleur
		 */
		Controleur controleur;

		/**
		 * \brief Scene
		 *
		 * La scène actuellement jouée à l'écran
		 *
		 * \see Scene
		 */
		ScenePtr scene;

		/**
		 * \brief Ressources
		 *
		 * Contient toutes les ressources du jeu
		 *
		 * \see Ressources
		 */
		Ressources ressources;

		/**
		 * \brief Horloge
		 *
		 * L'horloge permettant de gérer le temps dans l'application
		 *
		 * \see sf::Clock
		 */
		sf::Clock horloge;

		/**
		 * \brief Réseau
		 *
		 * La connexion réseau à un serveur 
		 *
		 * \see ReseauClient
		 */
		ReseauPtr reseau;

	public:
		/**
		 * \brief Constructeur
		 *
		 * Créé une nouvelle instance du Jeu
		 */
		Jeu();

		/**
		 * \brief Destructeur
		 *
		 * Détruit une instance précédemment créé du jeu
		 */
		virtual ~Jeu();

		/**
		 * \brief Remplace la scène actuelle par celle passée en paramètre
		 *
		 * Change la scène actuelle par la nouvelle passée en paramètre
		 *
		 * \param nouvelleScene la nouvelle scène
		 */
		void changer(Scene::Type nouvelleScene);

		/**
		 * \brief Lance le jeu
		 *
		 * Lance l'instance du jeu qui a été créé
		 */
		void lancer();

		/**
		 * \brief Quitter le jeu
		 *
		 * Quitte le jeu proprement
		 */
		void quitter();

		void connexionServeur(string ip, unsigned short port);

		/**
		 * \brief Récupère l'affichage
		 *
		 * Permet d'accéder à la fenêtre affichant le jeu
		 *
		 * \return l'affichage actuel
		 */
		Affichage& lireAffichage();
		/**
		 * \brief Récupère le modèle
		 *
		 * Permet d'accéderau modèle actuel
		 *
		 * \return le modèle actuel
		 */
		Plateau& lirePlateau();
		/**
		 * \brief Récupère le contrôleur
		 *
		 * Permet d'accéder au contrôleur actuel
		 *
		 * \return le contrôleur actuel
		 */
		Controleur& lireControleur();

		/**
		 * \brief Récupère les ressources
		 *
		 * Permet d'accéder aux différentes ressources du jeu
		 *
		 * \return les ressources du jeu
		 */
		Ressources& lireRessources();

		ReseauPtr& lireReseau();
};

#endif /* JEU_HPP */
