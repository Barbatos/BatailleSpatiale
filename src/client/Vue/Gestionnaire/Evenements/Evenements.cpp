#include "Evenements.hpp"

/**
 * Constructeur.
 */
Evenements::Evenements() {
	
}

/**
 * Destructeur.
 */
Evenements::~Evenements() {
	
}

/**
 * Vérifie les évènements.
 */
void Evenements::check(Affichage& affichage) {
    
    sf::Event event;
    
    while(affichage.pollEvent(event)) {
	switch(event.type) {
	    case sf::Event::Closed:
		affichage.close();
		break;
	    case sf::Event::KeyPressed:
		switch(event.key.code) {
		    case sf::Keyboard::Escape:
			affichage.close();
			break;
		    default:
			break;
		}
		break;
	    default:
		break;
	}
    }
}
