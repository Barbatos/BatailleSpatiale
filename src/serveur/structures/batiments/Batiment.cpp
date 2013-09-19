#include "Batiment.hpp"
#include "TypeBatiment.hpp"

sf::Texture Batiment::textureBatiment[BatimentNbrTotal] = {sf::Texture(), sf::Texture()};
sf::CircleShape Batiment::spriteBatiment[BatimentNbrTotal] = {sf::CircleShape(), sf::CircleShape()};

Batiment::Batiment() : Structure(){
    niveau = 0;

}

Batiment::Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, TypeBatiment _type) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque){
    this->niveau = niveau;
    type = _type;

}

int Batiment::getNiveau(){
    return niveau;

}

void Batiment::setNiveau(int niveau){
    this->niveau = niveau;

}

const void Batiment::afficherGraphiquement(sf::RenderWindow& fenetre, int i , int j){
	Structure::afficherGraphiquement(fenetre, i, j);
	Batiment::spriteBatiment[type].setPosition(i, j);
	fenetre.draw(Batiment::spriteBatiment[type]);
}

const TypeBatiment Batiment::getType(){
	return type;
}

void Batiment::chargerGraphismes(int taille){
		
	if (!Batiment::textureBatiment[BatimentBase].loadFromFile("ressources/base.png")){
		std::cout << "Erreur au chargement de la texture du batimentBase" << std::endl;
	}
	if (!Batiment::textureBatiment[BatimentVide].loadFromFile("ressources/manque.jpg")){
		std::cout << "Erreur au chargement de la texture du batiment inconnu" << std::endl;
	}
	for(int i = 0 ; i < BatimentNbrTotal; i++)
		Batiment::spriteBatiment[i] = sf::CircleShape(taille*3/5, 6);
		
	
	Batiment::spriteBatiment[BatimentBase].setTexture(&(Batiment::textureBatiment[BatimentBase]));
	Batiment::spriteBatiment[BatimentVide].setTexture(&(Batiment::textureBatiment[BatimentVide]));
}
