/*
 * ChargementServeurs.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: soinou
 */

#include "ChargementServeurs.hpp"

#include <client/vue/Affichage.hpp>

ChargementServeurs::ChargementServeurs(Gui* gui, int id, int x, int y,
		int largeur, int hauteur) :
		Element(gui, id), texte(), image(gui, -1, x, y, largeur,
				hauteur - texte.getCharacterSize() - 5, true, true,
				"Interface/chargement.png") {
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	texte.setString("En attente de la liste de serveurs ...");
	texte.setFont(
			gui->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
	texte.setPosition(x + (largeur - texte.getGlobalBounds().width) / 2,
			y + (hauteur - texte.getCharacterSize()));
}

ChargementServeurs::~ChargementServeurs() {

}

void ChargementReseau::actualiser(float) {
	//if (lireGui()->lireScene()->lireJeu().lireReseau()->getListeServeurs()) {
	Message message;

	message.type = Message::Element;

	message.element.clic = true;
	message.element.id = lireId();

	envoyerMessage(message);
	//}
}

void ChargementReseau::afficher() {
	affichage.draw(texte);
}

bool ChargementReseau::contient(sf::Vector2i) {
	return false;
}
