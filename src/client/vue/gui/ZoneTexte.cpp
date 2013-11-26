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

// Includes de nos classes
#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

ZoneTexte::ZoneTexte(int nom, int x, int y, int largeur, int hauteur) :
		Element(nom, x, y, largeur, hauteur),
		ElementSouris(),
		ElementClavier(),
		rectangle(),
		curseur(),
		label(),
		survole(false),
		selectionne(false),
		texte()
{
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
}

ZoneTexte::~ZoneTexte()
{

}

std::string ZoneTexte::lireTexte()
{
	return texte;
}

void ZoneTexte::initialiser()
{
	// On change la police de la zone
	label.setFont(parent->lireJeu().lireRessources().lirePolice("grand9k.ttf"));
}

void ZoneTexte::actualiser(__attribute__((unused)) float delta)
{
	// On change la couleur de la bordure selon que la zone soit selectionnée,
	// survolée, ou rien du tout
	if (selectionne)
		rectangle.setOutlineColor(sf::Color(255, 0, 0));
	else if (survole)
		rectangle.setOutlineColor(sf::Color(255, 255, 0));
	else
		rectangle.setOutlineColor(sf::Color(255, 255, 255));
}

void ZoneTexte::afficher(Affichage& affichage)
{
	// On dessine le rectangle, le label, et si la zone est selectionnée,
	// le curseur
	affichage.draw(rectangle);
	affichage.draw(label);

	if (selectionne)
		affichage.draw(curseur);
}

void ZoneTexte::surMouvementSouris(sf::Event::MouseMoveEvent evenement)
{
	// Si le rectangle contient la souris
	if (rectangle.getGlobalBounds().contains(evenement.x, evenement.y))
	{
		// Elle est survole
		survole = true;
	}
	// Sinon
	else
	{
		// Elle ne l'est pas
		survole = false;
	}
}

void ZoneTexte::surPressionBoutonSouris(__attribute__((unused)) sf::Event::MouseButtonEvent evenement)
{

}

void ZoneTexte::surRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement)
{
	// Si la zone est survole et que le bouton est le bouton gauche
	if (survole && evenement.button == sf::Mouse::Left)
	{
		// On selectionne la zone
		selectionne = true;
	}
	// Sinon
	else
	{
		// On la déselectionne / ne fait rien
		selectionne = false;
	}
}

void ZoneTexte::surMoletteSouris(__attribute__((unused)) sf::Event::MouseWheelEvent evenement)
{

}

void ZoneTexte::surPressionToucheClavier(__attribute__((unused)) sf::Event::KeyEvent evenement)
{
}

void ZoneTexte::surRelachementToucheClavier(__attribute__((unused)) sf::Event::KeyEvent evenement)
{

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

void ZoneTexte::surTexteClavier(sf::Event::TextEvent evenement)
{
	// Si la zone est selectionnée et ne dépasse pas du rectangle
	if (selectionne)
	{
		// Si le texte entré fait partie des caractères autorisé, et qu'on ne dépasse pas du rectangle
		if (estAutorise(evenement.unicode) && label.getGlobalBounds().width < rectangle
				.getSize().x - 20)
		{
			// On transforme le caractère entré depuis son format unicode
			char c = (char) evenement.unicode;

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
		else if (evenement.unicode == 8)
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
				<< evenement.unicode
				<< " : "
				<< (char) evenement.unicode
				<< std::endl;
		}

	}
}
