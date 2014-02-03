/*
 * BarreStatut.cpp
 *
 *  Created on: 3 févr. 2014
 *      Author: Tendry
 */

#include "BarreStatut.hpp"

BarreStatut::BarreStatut(Gui* gui, float x, float y, float largeur,
		float hauteur, sf::Color color, sf::Color color2) :
		BarreMesure(gui,x,y,largeur,hauteur), normale(color), critique(color2)
{
	progression.setFillColor(critique);
}

BarreStatut::~BarreStatut()
{

}

void BarreStatut::afficher(sf::RenderWindow& affichage)
{
	affichage.draw(contour);
	affichage.draw(progression);
	affichage.draw(description);
}

void BarreStatut::setValeurMontree(int value)
{
	if(value < 50)
		progression.setFillColor(critique);

	if(value > 50 && progression.getFillColor() == critique)
		progression.setFillColor(normale);

	std::stringstream stream;
	stream << value;
	description.setString(stream.str());
}

