#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "../Structure.hpp"
#include "TechnologieVaisseau.hpp"
#include "TypeVaisseau.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

/*
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Vaisseau : public Structure {

    public:
        Vaisseau();
        Vaisseau(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque,
			int _energieMax, int consommationMax , TypeVaisseau _type = VaisseauVide);
        // Getters
        int getEnergie() const;
        int getEnergieMax() const;
        int getConsommationMax() const;
		const int distanceMaximale();
		
        // Setters
        void setEnergie(int const energie);
        void setEnergieMax(int const energieMax);
        void setConsommationMax(int const consommationMax);

        void modifierEnergie(int const valeur);
        static Vaisseau cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV);

        void afficher(std::ostream& fluxSortant) const;
		const void afficherGraphiquement(sf::RenderWindow& fenetre, int i, int j);
		static void chargerGraphismes(int taille);
	
	protected:
		TypeVaisseau type;
		static sf::Texture textureVaisseau[VaisseauNbrTotal];
		static sf::CircleShape spriteVaisseau[VaisseauNbrTotal];

    private:
        int energie;
        int energieMax;
        int consommationMax;
        friend std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);

};

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP

