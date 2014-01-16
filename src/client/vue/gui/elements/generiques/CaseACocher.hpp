/*
 * CaseACocher.hpp
 *
 *  Created on: 21 nov. 2013
 *      Author: Tahiry
 */

#ifndef CASEACOCHER_HPP
#define CASEACOCHER_HPP

#include "GeneriquesPack.hpp"

/**
 * Case à cocher, indique qu'un élément est selectioné
 *
 * Todo: Documenter la CaseACocher
 */
class CaseACocher : public Element , public ObservateurSouris {
private:
	sf::RectangleShape boite;
	bool clique;

public:
	CaseACocher(Gui* gui, int id, int x, int y, float largeur,
	            float hauteur);
	virtual ~CaseACocher();

	bool estCoche();
	void actualiser(float delta);
	void afficher(sf::RenderWindow& affichage);
	bool contient(sf::Vector2i position);

	void clicSouris();
	void pressionSouris(sf::Mouse::Button bouton);
	void relachementSouris(sf::Mouse::Button bouton);
	void entreeSouris(sf::Vector2f position);
	void sortieSouris(sf::Vector2f position);
	void moletteSouris(int delta);
};

#endif /* CASEACOCHER_HPP */
