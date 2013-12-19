/*
 * SceneChargementJeu.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTJEU_HPP
#define SCENECHARGEMENTJEU_HPP

#include "ScenesPack.hpp"

class SceneChargementJeu :
	public Scene
{
	private:
		enum Elements
		{

		};

	public:
		SceneChargementJeu(Jeu& jeu);
		virtual ~SceneChargementJeu();

		void surMessage(int id);
};

#endif /* SCENECHARGEMENTJEU_HPP */
