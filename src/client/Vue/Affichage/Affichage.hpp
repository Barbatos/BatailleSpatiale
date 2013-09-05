#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include <SFML/Graphics.hpp>

/**
 * Classe Affichage, hérite de sf::RenderWindow, correspond à la fenêtre de rendu.
 */
class Affichage : public sf::RenderWindow {
	
	public:
		//Constructeur.
		Affichage();
		//Destructeur.
		~Affichage();
		
		//Créé l'affichage.
		void creer();
		
	private:
		//Si on est en plein écran, et si la synchro verticale est activée.
		//TODO : Créer un fichier de config qui initialise ces deux variables.
		bool fullscreen;
		bool vSync;
};

#endif
