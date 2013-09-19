#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "../vaisseaux/Vaisseau.hpp"
#include "TypeBatiment.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments.
 */
 
class Batiment : public Structure {

    public:
		Batiment();
		Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, TypeBatiment _type = BatimentVide);
		const void afficherGraphiquement(sf::RenderWindow& fenetre, int i , int j);
		const TypeBatiment getType();
		int getNiveau();
		void setNiveau(int niveau);
		static void chargerGraphismes(int taille);

	protected:
		TypeBatiment type;
		static sf::Texture textureBatiment[BatimentNbrTotal];
		static sf::CircleShape spriteBatiment[BatimentNbrTotal];

    private:
		int niveau;
};

typedef std::shared_ptr<Batiment> BatimentPtr;

#endif // BATIMENT_HPP


