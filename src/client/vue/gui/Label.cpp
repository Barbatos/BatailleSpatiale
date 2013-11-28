/*
 * Label.cpp
 *
 *  Created on: 5 oct. 2013
 *      Author: Soinou
 */

#include "Label.hpp"

// Moche, à changer plus tard par une CVar
#define TAILLE_TEXTE 14

Label::Label() : sf::Text()
{
	setCharacterSize(TAILLE_TEXTE);
}

Label::Label(std::string texte, float x, float y) : sf::Text()
{
	setString(texte);
	setPosition(x, y);
	setCharacterSize(TAILLE_TEXTE);
}

Label::Label(std::string texte, float x, float y, sf::Font& police) : sf::Text(texte, police, TAILLE_TEXTE)
{
	setPosition(x, y);
}

Label::~Label()
{

}
