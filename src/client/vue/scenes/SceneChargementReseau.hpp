/*
 * SceneChargementReseau.hpp
 *
 *  Created on: 19 déc. 2013
 *      Author: Soinou
 */

#ifndef SCENECHARGEMENTRESEAU_HPP
#define SCENECHARGEMENTRESEAU_HPP

#include "ScenesPack.hpp"

class SceneChargementReseau :
	public Scene
{
	private:
		enum Elements
		{

		};

	public:
		SceneChargementReseau(Jeu& jeu);
		virtual ~SceneChargementReseau();

		void surMessage(int id);
};

#endif /* SCENECHARGEMENTRESEAU_HPP_ */
