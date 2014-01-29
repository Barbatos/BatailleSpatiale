/*
 * BarreMesure.h
 *
 *  Created on: 29 janv. 2014
 *      Author: Tahiry
 */

#ifndef BARREMESURE_H_
#define BARREMESURE_H_

#include "GeneriquesPack.hpp"

/**
 * \brief représente une barre avec une mesure pouvant indiquer la valeur d'une propriété d'un joueur
 */
class BarreMesure: public Element {
private:
	/**
	 * \brief le contour de la barre de mesure
	 */
	sf::RectangleShape contour;

	/**
	 * \brief la progression dans la barre sous forme de petite barre
	 */
	sf::RectangleShape progression;

	/**
	 * \brief descriptif de la variable indiquée par la barre
	 */
	Label description;

	/**
	 * \brief le coefficient de multiplication pour l'affichage de la progression
	 */
	float coefficient;

public:
	/**
	 * \brief Version typedef de la barre
	 */
	typedef std::shared_ptr<BarreMesure> Ptr;

	BarreMesure();

	/**
	 * \brief Constructeur
	 *
	 * Créé une nouvelle barre de mesure avec les paramètres donnés
	 *
	 * \param gui le gui contenant la barre
	 * \param le texte associé a la description
	 * \param x sa position en x
	 * \param y sa position en y
	 * \param largeur sa largeur
	 * \param hauteur sa hauteur
	 */
	BarreMesure(Gui* gui, std::string texte, float x, float y, float largeur,
			float hauteur);

	/**
	 * \brief destructeur de l'objet
	 */
	virtual ~BarreMesure();

	void afficher(sf::RenderWindow& affichage);
	void actualiser(float);
	bool contient(sf::Vector2i);
};

#endif /* BARREMESURE_H_ */
