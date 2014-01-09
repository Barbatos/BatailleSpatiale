/*
 * SceneChargementJeuMulti.hpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTJEUMULTI_HPP
#define SCENECHARGEMENTJEUMULTI_HPP

#include "ScenesPack.hpp"

class SceneChargementJeuMulti :
	public Scene
{
	private:
		enum Elements
		{

		};

	public:
		SceneChargementJeuMulti(Jeu& jeu);
		virtual ~SceneChargementJeuMulti();

		void surMessage(int id);
};

#endif /* SCENECHARGEMENTJEUMULTI_HPP */
