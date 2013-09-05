#include "VueGraphique.hpp"

/**
 * Constructeur. 
 */
VueGraphique::VueGraphique() : Vue(), affichage(), gestionnaire() {
	
}

/**
 * Destructeur
 */
VueGraphique::~VueGraphique() {
	
}

/**
 * Initialise la vue.
 */
void VueGraphique::initialiser() {
	
	affichage.creer();
}

/**
 * Lance la vue.
 */
void VueGraphique::lancer() {
	sf::Sprite background;
	
	background.setTexture(*ressources.getTexture("background"));
	
	background.setScale(affichage.getSize().x/background.getGlobalBounds().width, affichage.getSize().y / background.getGlobalBounds().height);
	
	//Tant que l'affichage est ouvert.
	while(affichage.isOpen()) {
	    
		//Effacer l'écran.
		affichage.clear();
		
		//Affiche le fond.
		affichage.draw(background);
		
        gestionnaire.update(clock.restart().asSeconds());
        
        gestionnaire.draw(affichage);
        
		//Afficher ce qu'on a dessiné.
		affichage.display();
		
		//Vérifier les évènements.
		evenements.check(affichage);
	}
}
