/*
 * BarreMesure.cpp
 *
 *  Created on: 29 janv. 2014
 *      Author: Tendry
 */

#include "BarreMesure.hpp"

BarreMesure::BarreMesure(Gui* gui, float x, float y, float largeur,
		float hauteur) :
		Element(gui, -1), contour(), progression(), description(), coefficient(
				0), max(0)
{
	contour.setOrigin(-2, -2);
	contour.setSize(sf::Vector2f(largeur, hauteur));
	contour.setOutlineColor(sf::Color(150, 150, 150));
	contour.setOutlineThickness(2);
	contour.setPosition(x - contour.getSize().x - 10, y + 10);

	progression.setOrigin(-2, -2);
	progression.setSize(sf::Vector2f(largeur, hauteur));
	progression.setPosition(x - progression.getSize().x - 10, y + 10);

	description.setFont(
			lireGui()->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
	description.setColor(sf::Color::Black);
	description.setPosition(
			contour.getPosition().x + (contour.getSize().x / 2) - 25,
			contour.getPosition().y);
}

BarreMesure::BarreMesure(Gui* gui, sf::Color color, float x, float y,
		float largeur, float hauteur, int max) :
		Element(gui, -1), contour(), progression(), description(), max(max)
{
	coefficient = largeur / max;

	contour.setOrigin(-2, -2);
	contour.setSize(sf::Vector2f(largeur, hauteur));
	contour.setFillColor(sf::Color(255, 255, 255));
	contour.setOutlineColor(sf::Color(150, 150, 150));
	contour.setOutlineThickness(2);
	contour.setPosition(x - contour.getSize().x - 10, y + 10);

	progression.setOrigin(-2, -2);
	progression.setSize(sf::Vector2f(max * coefficient, hauteur));
	progression.setFillColor(color);
	progression.setPosition(x - progression.getSize().x - 10, y + 10);

	description.setFont(
			lireGui()->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
	description.setColor(sf::Color::Black);
	description.setPosition(
			contour.getPosition().x + (contour.getSize().x / 2) - 25,
			contour.getPosition().y);
}

BarreMesure::~BarreMesure()
{

}

void BarreMesure::actualiser(float)
{

}

void BarreMesure::afficher(sf::RenderWindow& affichage)
{
	affichage.draw(contour);
	affichage.draw(progression);
	affichage.draw(description);
}

void BarreMesure::setLargeur(int arg)
{
	progression.setSize(
			sf::Vector2f(arg * coefficient, progression.getSize().y));
}

void BarreMesure::setValeurMontree(int value)
{
	std::stringstream stream;
	stream << value;
	stream << "/";
	stream << max;
	description.setString(stream.str());
}

void BarreMesure::rendreInvisible()
{
	contour.setScale(0, 0);
	progression.setScale(0, 0);
	description.setScale(0, 0);
}

void BarreMesure::rendreVisible()
{
	contour.setScale(1, 1);
	progression.setScale(1, 1);
	description.setScale(1, 1);
}

sf::RectangleShape BarreMesure::getContour()
{
	return contour;
}

bool BarreMesure::contient(sf::Vector2i)
{
	return false;
}

