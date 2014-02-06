/*
 * GestionnaireSons.hpp
 *
 *  Created on: 6 févr. 2014
 *      Author: Tendry
 */

#ifndef GESTIONNAIRESONS_HPP_
#define GESTIONNAIRESONS_HPP_

#include <sfml/System/Clock.hpp>
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
		 * \brief Destructeur de l'objet
		 */
		virtual ~GestionnaireSons();
};

#endif /* GESTIONNAIRESONS_HPP_ */
