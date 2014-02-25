/*
 * GestionnaireSons.hpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#ifndef GESTIONNAIRESONS_HPP_
#define GESTIONNAIRESONS_HPP_

#include <SFML/System/Clock.hpp>
#include <client/ressources/Ressources.hpp>

/**
 *\brief classe qui gère les différents sons qui seront joués dans l'application
 */

class GestionnaireSons
{
	private:

		/**
		* \brief les ressources du jeu
		*/
		Ressources* ressources;

		/**
		 * \brief l'horloge générale du jeu
		 */
		sf::Clock horloge;

		/**
		 * \brief la musique courramment jouée
		 */
		Ressources::MusicPtr musique;

		/**
		 * \brief indique si on est en phase de jeu
		 */
		bool phaseDeJeu;

		/**
		 * \brief le temps de changement d'intensité en phase de jeu
		 */
		int tempsChangement;

		/**
		 * \brief indique si le gestionnaire a changé d'intensité
		 */
		bool aChangeIntensite;

	public:

		/**
		 * \brief Constructeur de l'objet
		 * \param ressources les ressources du jeu vidéo
		 */
		GestionnaireSons(Ressources* ressources);

		/**
		 * \brief lance la chanson actuellement traitée
		 */
		void lancerChanson();

		/**
		 * \brief stoppe la chanson actuellement traitée
		 */
		void stopperChanson();

		/**
		 * \brief lance ou désactive la chanson actuellement traitée
		 */
		void playPauseChanson();

		/**
		 * \brief change la chanson actuellement traitée
		 * \param pointeur la nouvelle chanson
		 */
		void changerChanson(Ressources::MusicPtr pointeur);

		/**
		 * \brief charge une musique dans le gestionnaire
		 * \param l'url de la musique
		 * \return un pointeur de type musique
		 */
		Ressources::MusicPtr chargerMusique(std::string texte);

		/**
		 * \brief indique si la musique en cour est déja traitée
		 * \param comparatif la musique dont on veut savoir si elle est traitée
		 * \return vrai ou faux
		 */
		bool dejaEnCour(Ressources::MusicPtr comparatif);

		/**
		 * \brief accesseur aux ressources du jeu
		 * \return un pointeur vers les ressources du jeu
		 */
		Ressources* lireRessources();

		/**
		 * \brief accesseur à la musique traitée
		 * \return un pointeur vers la musique
		 */
		Ressources::MusicPtr lireMusique();

		/**
		 * \brief accesseur à la phase de jeu
		 * \return vrai ou faux
		 */
		bool lirePhaseDeJeu();

		/**
		 * \brief modificateur de la phase de jeu
		 * \param la nouvelle valeur de la phase de jeu
		 */
		void ecrirePhaseDeJeu(bool value);

		/**
		 * \brief accesseur au temps de changement
		 * \return le temps de changement entre deux intensités
		 */
		int lireTempsChangement();

		/**
		 * \brief modifie le temps de changement entre intensités
		 *
		 * 	Démarre l'horloge pour mesurer le temps écoulé
		 *
		 * \param la nouvelle valeur
		 */
		void ecrireTempsChangement(int value);

		/**
		 * \brief controle et change la musique du jeu en fonction de l'intensite
		 */
		void controlerIntensite();

		/**
		 * \brief Destructeur de l'objet
		 */
		virtual ~GestionnaireSons();
};

#endif /* GESTIONNAIRESONS_HPP_ */
