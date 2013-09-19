#include "Plateau.hpp"
#include <SFML/Graphics.hpp>

sf::CircleShape Plateau::cercleSelection(0, 6);
sf::CircleShape Plateau::cercleMouvement(0, 6);

Plateau::Plateau(int _longueur, int _largeur, int _taille) :
	longueur(_longueur), largeur(_largeur), taille(_taille) {
	
	Plateau::chargerGraphismes(_taille);
	
	cellule.resize(_longueur, std::vector<Cellule>(_largeur));
		
	for (unsigned int i = 0 ; i < _longueur ; ++i)
		for (unsigned int j = 0 ; j < _largeur ; ++j)
            cellule[i][j] = Cellule();
	cellule[1][1].creerBatimentBaseTest();
	
	zoneParcourable = std::list<Noeud>();
	
	hexagone = sf::CircleShape(taille*3/5.0f, 6);
	hexagone.setOutlineThickness(0);
	numeroJoueur = 0;
	couleurJoueur = sf::Color::Blue;
	positionPrecedente = Point(-1, -1);
}

bool Plateau::accessible(const Point& point) {
	if(point.x < 0 || point.y < 0)
		return false;
	if(point.x >= longueur || point.y >= largeur)
		return false;
	switch(cellule[point.x][point.y].statutEmplacement()){
		case CelluleBatiment:
		case CelluleVaisseau:
		case CelluleEvenement:
			return false;
		default:
			break;
		}
		return true;
}

std::list<Point> Plateau::accessibleAutour(const Point& point){
	std::list<Point> autour;
	Point nouveauPoint;
	for(int i = 0; i < 6; i++) {
		nouveauPoint.set(point);
		switch(i) {
			case 0:
				nouveauPoint.x--;
				break;
			case 1:
				nouveauPoint.x++;
				break;
			case 2:
				nouveauPoint.y--;
				break;
			case 3:
				nouveauPoint.y++;
				break;
			case 4:
				nouveauPoint.x++;
				nouveauPoint.y--;
				break;
			case 5:
				nouveauPoint.x--;
				nouveauPoint.y++;
				break;
			default:
				break;
		}
		if(accessible(nouveauPoint))
			autour.push_back(Point(nouveauPoint));
	}
	return autour;
}

std::list<Point> Plateau::celluleAutour(const Point& point){
	std::list<Point> autour;
	Point nouveauPoint;
	for(int i = 0; i < 6; i++) {
		nouveauPoint.set(point);
		switch(i) {
			case 0:
				nouveauPoint.x--;
				break;
			case 1:
				nouveauPoint.x++;
				break;
			case 2:
				nouveauPoint.y--;
				break;
			case 3:
				nouveauPoint.y++;
				break;
			case 4:
				nouveauPoint.x++;
				nouveauPoint.y--;
				break;
			case 5:
				nouveauPoint.x--;
				nouveauPoint.y++;
				break;
			default:
				break;
		}
		if(nouveauPoint.x >= 0 && nouveauPoint.y >= 0 && nouveauPoint.x < longueur && nouveauPoint.y < largeur)
			autour.push_back(Point(nouveauPoint));
	}
	return autour;
}

int Plateau::coutDeplacement(Point point){
	return cellule[point.x][point.y].getCoutDeplacement();
}

const void Plateau::afficher(sf::RenderWindow& fenetre){
	for (int i = 0; i < longueur; i++) {
		for (int j = 0; j < largeur; j++) {
			hexagone.setPosition((i * 2 + j) * taille * 3/5, j * taille);
			fenetre.draw(hexagone);
		}
	}
	
	for(Noeud noeud : zoneParcourable){
		cercleMouvement.setPosition((noeud.getPoint().x * 2 + noeud.getPoint().y) * taille * 3/5, noeud.getPoint().y * taille);
		fenetre.draw(Plateau::cercleMouvement);
	}
	
	
	for (int i = 0; i < longueur; i++) {
		for (int j = 0; j < largeur; j++) {
			cellule[i][j].afficher(fenetre, (i * 2 + j) * taille * 3/5, j * taille);
		}
	}
	
	
	if(positionPrecedente.x != -1){
		cercleSelection.setPosition((positionPrecedente.x * 2 + positionPrecedente.y) * taille * 3/5, positionPrecedente.y * taille);
		fenetre.draw(Plateau::cercleSelection);
	}
}

Point Plateau::positionCellule(sf::Vector2f souris){
	Point point((((int) souris.x) / (taille*3/5) 
		- ((int) souris.y) /taille)/2, ((int) souris.y) /taille);
	
	if((point.x>=0 && point.x<longueur) && (point.y>=0 && point.y<largeur))
		return point;
	else
		return Point(-1, -1);
}

void Plateau::clicGaucheSouris(sf::Vector2f souris){
	Point position = positionCellule(souris);
	std::list<Point> autour = std::list<Point>();
	if(position.x != -1){
		autour = celluleAutour(position);
		switch(cellule[position.x][position.y].statutEmplacement()){
			case CelluleVide:
				for(Noeud noeud : zoneParcourable){
					if( position.estEgal(noeud.getPoint()) ) {
						VaisseauPtr vaisseau = cellule[positionPrecedente.x][positionPrecedente.y].getVaisseau();
						vaisseau->modifierEnergie(-1 * noeud.getG());
						cellule[position.x][position.y].setVaisseau(vaisseau);
						cellule[positionPrecedente.x][positionPrecedente.y].retirerVaisseau();
						positionPrecedente = position;
					}
				}
				if(cellule[position.x][position.y].getType() == CelluleVide){
					for(Point point : autour){
						if(cellule[point.x][point.y].typeBatiment() == BatimentBase)
							cellule[position.x][position.y].creerVaisseauConstructeurTest();
					}
				}
				creerZoneParcourable();
				break;
			case CelluleVaisseau:
			case CelluleBatiment:
				if(positionPrecedente.x != -1){
					if(cellule[positionPrecedente.x][positionPrecedente.y].statutEmplacement() == CelluleBatiment ||
						cellule[positionPrecedente.x][positionPrecedente.y].statutEmplacement() == CelluleVaisseau)
						cellule[position.x][position.y].subir(cellule[positionPrecedente.x][positionPrecedente.y].getAttaquant());
					else
						positionPrecedente = position;
				}
				break;
			default:
				break;
		}
				
				
	}
}

void Plateau::clicDroitSouris(sf::Vector2f souris){
	Point position = positionCellule(souris);
	std::list<Point> autour = std::list<Point>();
	if(position.x != -1){
		autour = celluleAutour(position);
		switch(cellule[position.x][position.y].statutEmplacement()){
			case CelluleVide:
				for(Point point : autour){
					if(cellule[point.x][point.y].typeBatiment() == BatimentBase)
						cellule[position.x][position.y].creerVaisseauTest();
				}
				creerZoneParcourable();
				break;
			default:
				positionPrecedente = position;
				creerZoneParcourable();
				break;
		}
				
				
	}
}

void Plateau::changerJoueurCourant(int numero, sf::Color couleur){
	numeroJoueur = numero;
	couleurJoueur = couleur;
}

void Plateau::chargerGraphismes(int _taille){
	Batiment::chargerGraphismes(_taille);
	Vaisseau::chargerGraphismes(_taille);
	Structure::chargerGraphismes(_taille);
	
	Plateau::cercleSelection.setFillColor(sf::Color::Transparent);
	Plateau::cercleSelection.setRadius(_taille * 3/5.0f);
	Plateau::cercleSelection.setOutlineThickness(5);
	Plateau::cercleSelection.setOutlineColor(sf::Color(71, 169, 215, 180));
	Plateau::cercleMouvement.setFillColor(sf::Color(0, 102, 14, 180));
	Plateau::cercleMouvement.setRadius(_taille * 3/5.0f);
}

void Plateau::creerZoneParcourable(){
	zoneParcourable.clear();
	if(positionPrecedente.x != -1){
		
		std::list<Noeud> openListe;
		std::list<Noeud>::iterator noeudIterateur;
			
		std::list<Point> pointAutour;
		std::list<Point>::iterator pointCourant;
		bool noeudTrouve = false;
		
		Noeud noeudCourant(positionPrecedente);
		int distanceParcourable = cellule[positionPrecedente.x][positionPrecedente.y].distanceMaximale();
		do{
			
			zoneParcourable.push_back(noeudCourant);
			
			// on le retire de l'openListe
			for(noeudIterateur = openListe.begin(); noeudIterateur != openListe.end(); noeudIterateur++){
				 if(noeudCourant.equal(*noeudIterateur))
						noeudIterateur = openListe.erase(noeudIterateur);
			}
			
			pointAutour.clear();
			pointAutour = celluleAutour(noeudCourant.getPoint());
			
			for(pointCourant = pointAutour.begin(); pointCourant != pointAutour.end(); pointCourant++){
				
				if(cellule[pointCourant->x][pointCourant->y].accessible()){
				
					noeudIterateur = openListe.begin();
					noeudTrouve = false;
					while(!noeudTrouve && noeudIterateur != openListe.end()){
						if(pointCourant->estEgal(noeudIterateur->getPoint())){
							noeudTrouve = true;
						}else{
							noeudIterateur++;
						}
					}
					if (noeudTrouve){
						if (noeudCourant.getG() + cellule[pointCourant->x][pointCourant->y].getCoutDeplacement() < noeudIterateur->getG()){
							
							noeudIterateur = openListe.erase(noeudIterateur);
							openListe.push_back(Noeud(*pointCourant, cellule[pointCourant->x][pointCourant->y].getCoutDeplacement(), noeudCourant.getPoint()));
						}
							
						
					} else {
						
						noeudIterateur = zoneParcourable.begin();
						noeudTrouve = false;
						while(!noeudTrouve && noeudIterateur != zoneParcourable.end()){
							if(pointCourant->estEgal(noeudIterateur->getPoint())){
								noeudTrouve = true;
							}else{
								noeudIterateur++;
							}
						}
						if (!noeudTrouve){
							openListe.push_back(Noeud(*pointCourant, cellule[pointCourant->x][pointCourant->y].getCoutDeplacement() + noeudCourant.getG(), noeudCourant.getPoint()));
						}
					}
				}
			}
			
			noeudCourant = *(openListe.begin());
			// On prend le noeud avec le G le plus bas
			for(noeudIterateur = openListe.begin(); noeudIterateur != openListe.end(); noeudIterateur++){
				if ((*noeudIterateur).lowerG(noeudCourant))
					noeudCourant = *noeudIterateur;
			}
			
		}while(!openListe.empty() && noeudCourant.getG() <= distanceParcourable);
	}
}
