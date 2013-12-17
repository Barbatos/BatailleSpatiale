/*
 * ZoneTexte.cpp
 *
 * Ne pas formater s'il vous plaît :(
 *
 *  Created on: 21 nov. 2013
 *      Author: Soinou
 */

#include "ZoneTexte.hpp"

// Includes de la libstd
#include <sstream>

ZoneTexte::ZoneTexte(Gui* gui, int id, int x, int y, int largeur, int hauteur,
	std::string remplacement) :
		Element(gui, id),
		ObservateurSouris(),
		ObservateurClavier(),
		rectangle(),
		curseur(),
		label(),
		survole(false),
		selectionne(false),
		texte(),
		remplacement(remplacement)
{
	ecrirePosition(x, y);
	ecrireTaille(largeur, hauteur);

	enregistrerSouris(ObservateurSouris::Ptr(this));
	enregistrerClavier(ObservateurClavier::Ptr(this));

	// On configure le rectangle (bordure)
	rectangle.setPosition(x, y);
	rectangle.setSize(sf::Vector2f(largeur, hauteur));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setFillColor(sf::Color(255, 255, 255, 0));

	// On configure le curseur
	curseur.setPosition(x + 5, y + (hauteur - label.getCharacterSize()) / 2);
	curseur.setSize(sf::Vector2f(1, label.getCharacterSize()));
	curseur.setOutlineThickness(1);
	curseur.setOutlineColor(sf::Color(255, 255, 255));

	// On configure le label
	label.setPosition(x + 5, y + (hauteur - label.getCharacterSize()) / 2);
	label.setColor(sf::Color(255, 255, 255));

	label.setString(remplacement);
	label.setFont(
			gui->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
}

ZoneTexte::~ZoneTexte()
{

}

std::string ZoneTexte::lireTexte()
{
	return texte;
}

void ZoneTexte::actualiser(float)
{
	// On change la couleur de la bordure selon que la zone soit selectionnée,
	// survolée, ou rien du tout
	if (selectionne)
		rectangle.setOutlineColor(sf::Color(255, 0, 0));
	else if (lireSurvol())
		rectangle.setOutlineColor(sf::Color(255, 255, 0));
	else
		rectangle.setOutlineColor(sf::Color(255, 255, 255));
}

void ZoneTexte::afficher(sf::RenderWindow& affichage)
{
	// On dessine le rectangle, le label, et si la zone est selectionnée,
	// le curseur
	affichage.draw(rectangle);
	affichage.draw(label);

	if (selectionne)
		affichage.draw(curseur);
}

bool ZoneTexte::contient(sf::Vector2i position)
{
	return rectangle.getGlobalBounds().contains(position.x, position.y);
}

bool ZoneTexte::estAutorise(int unicode)
{
	// Caractères autorisés : caractères alphanumériques, espaces et points
	return (unicode >= 65 && unicode <= 90) // A - Z
	|| (unicode >= 97 && unicode <= 122) // a - z
	|| (unicode >= 48 && unicode <= 57) // 0 - 9
	|| unicode == 46 // .
	|| unicode == 32; // Espace
}

void ZoneTexte::clicSouris()
{
	// On selectionne la zone
	selectionne = true;

	if (texte.empty())
		label.setString("");
}

void ZoneTexte::pressionSouris(sf::Mouse::Button)
{
	if (!lireSurvol())
	{
		selectionne = false;

		if (texte.empty())
			label.setString(remplacement);
	}
}

void ZoneTexte::relachementSouris(sf::Mouse::Button)
{

}

void ZoneTexte::entreeSouris(sf::Vector2f)
{

}

void ZoneTexte::sortieSouris(sf::Vector2f)
{
}

void ZoneTexte::moletteSouris(int)
{

}

void ZoneTexte::pressionTouche(sf::Keyboard::Key)
{

}

void ZoneTexte::relachementTouche(sf::Keyboard::Key)
{

}

void ZoneTexte::entreeTexte(sf::Uint32 unicode)
{

	// Si la zone est selectionnée et ne dépasse pas du rectangle
	if (selectionne)
	{
		// Si le texte entré fait partie des caractères autorisé, et qu'on ne dépasse pas du rectangle
		if (estAutorise(unicode) && label.getGlobalBounds().width < rectangle
				.getSize().x - 20)
		{
			// On transforme le caractère entré depuis son format unicode
			char c = (char) unicode;

			// On l'ajoute au texte actuel
			std::stringstream stream;
			stream
				<< texte
				<< c;
			texte = stream.str();

			// On met à jour le label
			label.setString(texte);

			// On change la position du curseur
			curseur.setPosition(
					label.getPosition().x + label.getGlobalBounds().width + 1,
					curseur.getPosition().y);
		}
		// Si le caractère entré est la touche de retour arrière
		else if (unicode == 8)
		{
			// On réduit le texte de 1 caractère
			texte = texte.substr(0, texte.size() - 1);

			// On met à jour le label
			label.setString(texte);

			// On met à jour le curseur
			if (texte.size() == 0)
				curseur.setPosition(rectangle.getPosition().x + 5,
									curseur.getPosition().y);
			else
				curseur.setPosition(
						label.getPosition().x + label.getGlobalBounds().width + 1,
						curseur.getPosition().y);
		}
		// Sinon (Temporaire, utilisé seulement pour du débug)
		else
		{
			// On affiche le caractère
			std::cout
				<< unicode
				<< " : "
				<< (char) unicode
				<< std::endl;
		}

	}
}
