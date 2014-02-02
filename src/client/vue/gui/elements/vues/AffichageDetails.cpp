/*
 * AffichageDetails.cpp
 *
 *  Created on: 18 oct. 2013
 *      Author: Soinou
 */

#include "AffichageDetails.hpp"

// Includes de la libstd
#include <string>
#include <sstream>
#include <iostream>

// Includes de nos classes
#include <client/vue/Affichage.hpp>
#include <client/Jeu.hpp>

// Includes des classes utiles
#include <utiles.hpp>

AffichageDetails::AffichageDetails(Gui* gui, int id, float x, float y,
		float largeur, float hauteur) :
		Element(gui, id), fondCase(), fondJoueurs(), infosCase("", x + 5,
				y + 5), infosJoueurs("", x + largeur - largeur / 3 + 5, y + 5), position(
				-1, -1)
{

	santeBatiment = NULL;
	santeVaisseau = NULL;

	Joueur* joueur = gui->lireScene()->lireJeu().lireJoueur();
	int xalign = x + largeur - 50;
	int xsize = 250;

	//Création des barres
	commandementBarre = new BarreMesure(gui, sf::Color::Magenta, xalign, y + 20,
			xsize, 10, joueur->getCommandement());
	energieBarre = new BarreMesure(gui, sf::Color::Green, xalign, y + 43, xsize,
			10, joueur->getEnergie());
	materiauxBarre = new BarreMesure(gui, sf::Color::Red, xalign, y + 65, xsize,
			10, joueur->getMateriaux());
	requisitionBarre = new BarreMesure(gui, sf::Color(200, 200, 150), xalign,
			y + 88, xsize, 10, joueur->getRequisition());

	int taille = largeur / 3;

	fondCase.setOrigin(-2, -2);
	fondCase.setPosition(x, y);
	fondCase.setSize(sf::Vector2f(taille - 4, hauteur - 4));
	fondCase.setFillColor(sf::Color(50, 50, 50));
	fondCase.setOutlineColor(sf::Color(100, 100, 100));
	fondCase.setOutlineThickness(2);

	fondJoueurs.setOrigin(taille - 2, -2);
	fondJoueurs.setPosition(x + largeur, y);
	fondJoueurs.setSize(sf::Vector2f(taille - 4, hauteur - 4));
	fondJoueurs.setFillColor(sf::Color(50, 50, 50));
	fondJoueurs.setOutlineColor(sf::Color(100, 100, 100));
	fondJoueurs.setOutlineThickness(2);

	infosCase.setFont(
			lireGui()->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
	infosJoueurs.setFont(
			lireGui()->lireScene()->lireJeu().lireRessources().lirePolice(
					"grand9k.ttf"));
}

AffichageDetails::~AffichageDetails()
{

}

void AffichageDetails::actualiser(float)
{
	Joueur* joueur = lireGui()->lireScene()->lireJeu().lireJoueur();
	// Mettre à jour les informations joueurs
	std::stringstream stream;

	stream << "Pseudo: ";
	stream << joueur->getPseudo();
	stream << "\n";
	stream << "Commandement: " << "\n";
	stream << "Energie: " << "\n";
	stream << "Materiaux: " << "\n";
	stream << "Requisition: " << "\n";

	//Mettre à jour la progression des barres
	commandementBarre->setLargeur(joueur->getCommandement());
	commandementBarre->setValeurMontree(joueur->getCommandement());

	energieBarre->setLargeur(joueur->getEnergie());
	energieBarre->setValeurMontree(joueur->getEnergie());

	materiauxBarre->setLargeur(joueur->getMateriaux());
	materiauxBarre->setValeurMontree(joueur->getMateriaux());

	requisitionBarre->setLargeur(joueur->getRequisition());
	requisitionBarre->setValeurMontree(joueur->getRequisition());

	infosJoueurs.setString(stream.str());
	//infosJoueurs.setOrigin(infosJoueurs.getGlobalBounds().width, 0);

	//Mechanisme pour lire ls infos du joueur(manque methode reseau)
	//lireGui()->lireScene()->lireJeu().lireReseauServeur().lireJoueurs();

	// On vérifie si aucune case n'est selectionnée
	if (position.x == -1 && position.y == -1)
	{
		// Si oui, on change le message et on termine l'actualisation
		infosCase.setString(std::wstring(L"Aucune case n'est selectionnée"));

		if (santeVaisseau != NULL)
			santeVaisseau->rendreInvisible();
		if(santeBatiment != NULL)
					santeBatiment->rendreInvisible();
		return;
	}

	// Sinon, on stocke le plateau et le type de la cellule
	Plateau p = lireGui()->lireScene()->lireJeu().lirePlateau();
	TypeCellule cellule = p.getCellule(position).statutEmplacement();
	std::wstring texte;

	// On récupère les informations liées à ce que contient cette cellule
	switch (cellule)
	{
	case TypeCellule::Vaisseau:
		if (p.getVaisseau(position).type == TypeVaisseau::Constructeur)
		{
			//TO-DO
		}
		texte = Utile::toString(p.getVaisseau(position));

		if (santeVaisseau == NULL)
		{
			santeVaisseau = new BarreMesure(lireGui(), sf::Color::Red,
					fondCase.getPosition().x + 300,
					fondCase.getPosition().y + 18, 250, 15,
					p.getVaisseau(position).vieMax);
			santeVaisseau->setLargeur(p.getVaisseau(position).vie);
		}

		santeVaisseau->rendreVisible();
		santeVaisseau->setLargeur(p.getVaisseau(position).vie);
		santeVaisseau->setValeurMontree(p.getVaisseau(position).vie);

		if(santeBatiment != NULL)
			santeBatiment->rendreInvisible();
		break;
	case TypeCellule::Batiment:
		texte = Utile::toString(p.getBatiment(position));

		if(santeBatiment == NULL)
		{
			santeBatiment = new BarreMesure(lireGui(), sf::Color::Red,
					fondCase.getPosition().x + 300,
					fondCase.getPosition().y + 39, 250, 15,
					p.getBatiment(position).vieMax);
			santeBatiment->setLargeur(p.getBatiment(position).vie);
		}

		santeBatiment->rendreVisible();
		santeBatiment->setLargeur(p.getBatiment(position).vie);
		santeBatiment->setValeurMontree(p.getBatiment(position).vie);

		if (santeVaisseau != NULL)
					santeVaisseau->rendreInvisible();
		break;
	case TypeCellule::Evenement:
		texte = Utile::toString(p.getEvenement(position));

		if (santeVaisseau != NULL)
			santeVaisseau->rendreInvisible();
		if(santeBatiment != NULL)
					santeBatiment->rendreInvisible();

		break;
	default:
		texte = Utile::toString(position);

		if (santeVaisseau != NULL)
			santeVaisseau->rendreInvisible();

		if(santeBatiment != NULL)
					santeBatiment->rendreInvisible();
		break;
	}

	// On change le message
	infosCase.setString(texte);
}

void AffichageDetails::afficher(sf::RenderWindow& affichage)
{
	affichage.draw(fondCase);
	affichage.draw(fondJoueurs);
	affichage.draw(infosCase);
	affichage.draw(infosJoueurs);
	commandementBarre->afficher(affichage);
	energieBarre->afficher(affichage);
	materiauxBarre->afficher(affichage);
	requisitionBarre->afficher(affichage);
}

bool AffichageDetails::contient(sf::Vector2i)
{
	return false;
}

void AffichageDetails::selectionner(int i, int j)
{
	position = Position(i, j);
}

void AffichageDetails::selectionner(Position position)
{
	this->position = position;
}

void AffichageDetails::selectionner()
{
	position = Position(-1, -1);
}

bool AffichageDetails::estSelectionne()
{
	return position.x != -1 && position.y != -1;
}

Position AffichageDetails::lirePosition()
{
	return position;
}
