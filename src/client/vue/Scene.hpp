/*
 * Scene.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef SCENE_HPP
#define SCENE_HPP

// Include de la SFML
#include <SFML/Window/Event.hpp>

// Includes de la libstd
#include <vector>
#include <memory>

// Includes de nos classes
#include "gui/Gui.hpp"

// Pré-déclarations
class Jeu;

/**
 * \brief Représente une scène du jeu
 */
class Scene
{
	protected:
		/**
		 *	\brief Référence vers le jeu
		 *
		 *	Une simple référence vers le jeu actuel
		 *
		 *	\see Jeu
		 */
		Jeu& jeu;

		/**
		 *
		 */
		Gui gui;

	public:

		/**
		 * \brief Version unique_ptr de la scène
		 */
		typedef std::unique_ptr<Scene> Ptr;

		/**
		 * \brief Les différentes scènes possibles
		 *
		 * Toutes les scènes possibles de l'interface
		 */
		enum Type
		{
			SceneMenuPrincipal, //!< Scène du Menu Principal
			SceneMenuSolo, //!< Scène du Menu de création d'une partie Solo
			SceneMenuMulti, //!< Scène du Menu de création d'une partie Multi
			SceneJeu, //!< Scène du Jeu
			SceneJeuMenu, //!< Scène du Menu en Jeu
			SceneJeuOptions, //!< Scène des Options en Jeu
			SceneOptionsMenu,
			SceneMenuMultijoueur,
			SceneLancerServeur //!< Scène du lancement d'un serveur de jeu
		};

		/**
		 * \brief Constructeur
		 *
		 * Instancie une nouvelle scène avec le jeu passé en paramètre
		 *
		 * @param jeu le jeu actuel
		 * \see Jeu
		 */
		Scene(Jeu& jeu);

		/**
		 * \brief Destructeur
		 *
		 * Détruit la scène précédemment créée
		 */
		virtual ~Scene();

		/**
		 * \brief Met à jour la scène
		 *
		 * Met à jour la scène selon le temps passé en paramètre
		 *
		 * \param delta le temps écoulé depuis le dernier affichage
		 */
		void actualiser();

		/**
		 * \brief Affiche la scène
		 *
		 * Affiche la scène telle qu'elle est actuellement
		 */
		void afficher();

		/**
		 * \brief Traite l'évènement donné
		 *
		 * Récupère un évènement et le traite
		 *
		 * @param evenement l'évènement à traiter
		 */
		void traiter(sf::Event& evenement);

		/**
		 * \brief Fonction appelée par les éléments de la scène
		 *
		 * Lorsqu'un élément présent dans la scène a besoin de lui envoyer une message,
		 * cette fonction est appelée
		 *
		 * @param nom le nom de l'élement
		 * @param message le message envoyé
		 * \see Message
		 */
		virtual void surMessage(int id) = 0;

		/**
		 * \brief Renvoie le jeu
		 *
		 * Renvoie une référence vers le jeu actuel, contenant la scène
		 *
		 * @return le jeu actuel
		 * \see Jeu
		 */
		Jeu& lireJeu();

		/**
		 *
		 * @return
		 */
		Gui& lireGui();

		/**
		 * \class Scene
		 *
		 * Définit une scène ou un écran du jeu.
		 *
		 * La scène contient des éléments, ajoutés grâce aux fonctions ajouterElement(),
		 * ajouterSouris() et ajouterClavier().
		 *
		 * Attention : ne pas ajouter un observateur clavier ou souris grâce à la fonction ajouterElement(),
		 * ou ses évènements ne seront pas traités.
		 *
		 * Exemple de création de nouvelle scène :
		 *
		 \code
		 class NouvelleScene : public Scene
		 {
		 public:
		 NouvelleScene(Jeu& jeu);
		 ~NouvelleScene() { }

		 void surMessage(std::string nom, Message message);
		 }

		 NouvelleScene::NouvelleScene(Jeu& jeu) : Scene(jeu)
		 {
		 ajouterElement(new Element("element"));
		 ajouterSouris(new ObservateurSouris("elementSouris"));
		 ajouterClavier(new ObservateurClavier("elementClavier"));
		 }

		 void NouvelleScene::surMessage(std::string nom, Message message)
		 {
		 switch(message)
		 {
		 case Clic:
		 if(nom == "elementSouris")
		 // elementSouris a été cliqué !
		 // Cet élément doit faire passer à la prochaine scène :
		 jeu.changer(Scene::NouvelleScene);

		 // Note : La classe Scene possède l'énumération Scene::Type regroupant
		 // toutes les scènes du jeu
		 break;
		 // Autres cas ...
		 }
		 }
		 \endcode
		 */
};

#endif /* SCENE_HPP */
