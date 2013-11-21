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

// Pré-déclarations
class Jeu;
class Element;
class ElementSouris;
class ElementClavier;

// Typedefs
typedef std::shared_ptr<Element> ElementPtr;
typedef std::shared_ptr<ElementSouris> SourisPtr;
typedef std::shared_ptr<ElementClavier> ClavierPtr;

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

	private:
		/**
		 * \brief Liste des éléments
		 *
		 * Liste des éléments présents dans la scène
		 *
		 * \see Element
		 */
		std::vector<ElementPtr> elements;

		/**
		 * \brief Liste des observateur souris
		 *
		 * Liste des observateur souris présents dans la scène
		 *
		 * \see ObservateurSouris
		 */
		std::vector<SourisPtr> souris;

		/**
		 * \brief Liste des observateur clavier
		 *
		 * Liste des observateur clavier présents dans la scène
		 *
		 * \see ObservateurClavier
		 */
		std::vector<ClavierPtr> clavier;

	public:

		/**
		 * \brief Type du message reçu
		 *
		 * message qu'un des éléments a envoyé
		 */
		enum Message
		{
			Clic, //!< Un élément a été cliqué
			Entre, //!< La souris est entrée dans un élément
			Sort, //!< La souris est sortie d'un élément
		};

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
		 * \brief Ajoute l'élément donné à la scène
		 *
		 * Récupère l'élément donné et l'ajoute à la scène
		 *
		 * \param element l'élément à rajouter
		 * \see Element
		 */
		void ajouter(Element* element);

		/**
		 * \brief Enregistre l'observateur souris donné
		 *
		 * Ajoute l'observateur souris donné et appelera ses fonctions de callback en cas d'évènement
		 *
		 * \param souris
		 */
		void enregistrerSouris(ElementSouris* souris);

		/**
		 * \brief
		 * \param clavier
		 */
		void enregistrerClavier(ElementClavier* clavier);

		/**
		 * \brief Met à jour la scène
		 *
		 * Met à jour la scène selon le temps passé en paramètre
		 *
		 * \param delta le temps écoulé depuis le dernier affichage
		 */
		void actualiser(float delta);

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
		virtual void surMessage(int nom, Message message) = 0;

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
