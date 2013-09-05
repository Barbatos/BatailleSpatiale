#ifndef EVENEMENTS_HPP
#define EVENEMENTS_HPP

#include "../Affichage/Affichage.hpp"

/**
 * Classe des évènements, classe qui s'occupe de gérer tout les évènements, et les envoyer aux objets en ayant besoin.
 */
class Evenements {
	public:
		//Constructeur.
		Evenements();
		//Destructeur.
		~Evenements();
		
		//Vérifie les évènements.
		void check(Affichage&);

};

#endif

