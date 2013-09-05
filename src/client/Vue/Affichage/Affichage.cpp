#include "Affichage.hpp"

/**
 * Constructeur.
 */
Affichage::Affichage() : sf::RenderWindow() {
    fullscreen = true;
    vSync = true;
}

/**
 * Destructeur.
 */
Affichage::~Affichage() {

}

/**
 * Créé l'affichage.
 */
void Affichage::creer() {
	//Mode Vidéo.
	sf::VideoMode vMode;
	
	//Drapeaux de la fenêtre.
	int flags;
	
	//Si on est en fullscreen.
	if(fullscreen) {
		//Initialiser le mode avec le plus haut mode plein écran.
		vMode = sf::VideoMode::getFullscreenModes()[0];
		//Dire qu'on est en plein écran.
		flags = sf::Style::Fullscreen;
	}
	//Sinon
	else {
		//Initialiser le mode avec le plus haut mode de bureau.
		vMode = sf::VideoMode::getDesktopMode();
		//Dire qu'on est en fenêtré.
		flags = sf::Style::Default;
	}
	
	//Créer la fenêtre.
	create(vMode, "Title", flags);
	
	//Activer ou non la synchro verticale.
	setVerticalSyncEnabled(vSync);
}
