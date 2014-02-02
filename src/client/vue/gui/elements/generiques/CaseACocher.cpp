/*
 * CaseACocher.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Tahiry
 */

#include "CaseACocher.hpp"
#include <client/vue/gui/Element.hpp>
#include <client/vue/Affichage.hpp>

/**
 * @brief Constructeur de l'objet
 */
CaseACocher::CaseACocher(Gui* gui, int id, int x, int y, float hauteur, float largeur, std::string txt)
                : Element(gui, id), ObservateurSouris(), boite(), clique(false), texte(txt, x+largeur+3 , y) {
    ecrirePosition(x, y);
    ecrireTaille(largeur, hauteur);

    enregistrerSouris(this);

    //creation de l'�l�ment
    sf::Vector2f size = sf::Vector2f(hauteur, largeur);
    boite.setSize(size);
    boite.setPosition(x,y);
    boite.setFillColor(sf::Color::White);
    boite.setOutlineThickness(3);
    boite.setOutlineColor(sf::Color::Magenta);
    texte.setFont(lireGui()->lireScene()->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
}

/**
 * Destructeur de l'objet
 */
CaseACocher::~CaseACocher() {

}

void CaseACocher::actualiser(float) {
}

void CaseACocher::afficher(sf::RenderWindow& affichage) {
    affichage.draw(boite);
    affichage.draw(texte);
}

bool CaseACocher::contient(sf::Vector2i position) {
    return boite.getGlobalBounds().contains(position.x, position.y);
}

bool CaseACocher::estCoche() {
    return clique;
}

void CaseACocher::clicSouris(bool clicDroit) {

	lireGui()->lireScene()->lireJeu().lireRessources().jouerSon("menuclick.wav");

    if (!clicDroit) {
        if (clique == true) {
            clique = false;
            boite.setFillColor(sf::Color::White);
        }
        else {
            clique = true;
            boite.setFillColor(sf::Color::Cyan);
        }
    }

    if(clique)
    {
    	Message message;

    	message.type = Message::Element;
    	message.element.clic = true;
    	message.element.id = lireId();

    	envoyerMessage(message);
    }
}
void CaseACocher::pressionSouris(sf::Mouse::Button) {

}

void CaseACocher::relachementSouris(sf::Mouse::Button) {

}

void CaseACocher::entreeSouris(sf::Vector2f) {
    sf::Color color(120, 120, 120);
    boite.setFillColor(color);
}

void CaseACocher::sortieSouris(sf::Vector2f) {
	if(!clique)
		boite.setFillColor(sf::Color::White);
	else
		boite.setFillColor(sf::Color::Cyan);
}

void CaseACocher::moletteSouris(int) {

}
