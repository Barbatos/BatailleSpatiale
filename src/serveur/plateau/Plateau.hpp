#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include <list>
#include "Point.hpp"
#include "Noeud.hpp"
#include "Cellule.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

/**
 * Cette classe contient toutes les cases du jeu
 */
class Plateau{
	public:
		Plateau(int _longueur, int _largeur, int _taille = 50);
		bool accessible(const Point& point);
		std::list<Point> accessibleAutour(const Point& point);
		std::list<Point> celluleAutour(const Point& point);
		int coutDeplacement(Point point);
		const void afficher(sf::RenderWindow& window);
		void clicDroitSouris(sf::Vector2f souris);
		void clicGaucheSouris(sf::Vector2f souris);
		void changerJoueurCourant(int numero, sf::Color couleur);
		Point positionCellule(sf::Vector2f souris);
		static void chargerGraphismes(int _taille);
		void creerZoneParcourable();
	
	protected:
		std::vector<std::vector<Cellule>> cellule;
		int longueur;
		int largeur;
		int taille;
		int numeroJoueur;
		sf::Color couleurJoueur;
		Point positionPrecedente;
		static sf::CircleShape cercleSelection;
		static sf::CircleShape cercleMouvement;
		
	private:
		std::list<Noeud> zoneParcourable;
		sf::CircleShape hexagone;

};

#endif // PLATEAU_HPP
