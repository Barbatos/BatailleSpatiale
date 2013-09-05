#ifndef VUEGRAPHIQUE_HPP
#define VUEGRAPHIQUE_HPP

#include "Vue.hpp"

#include "Affichage/Affichage.hpp"
#include "Gestionnaire/Gestionnaire.hpp"

/**
 * Classe Vue Graphique, correspond à la vue du pattern MVC, marchant avec la SFML.
 */
class VueGraphique : public Vue{
	
	public:
		//Constructeur.
		VueGraphique();
		//Destructeur.
		virtual ~VueGraphique();
		//Initialise la vue.
		void initialiser();
		//Lance la vue.
		void lancer();

	private:
		//L'affichage.
		Affichage affichage;
		//Les évènements.
		Evenements evenements;
		//Les ressources.
		Ressources ressources;
        //Le gestionnaire.
        Gestionnaire gestionnaire;
        //La clock de la SFML
        sf::Clock clock;
};

#endif
