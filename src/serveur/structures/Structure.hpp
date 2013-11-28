#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#include "TechnologieStructure.hpp"
#include <memory>

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments et les vaisseaux.
 * Les classes Vaisseau et Batiment en héritent
 */

class Structure{

    public:

        Structure(int _vieMax = 100, int _bouclierMax = 0, float _bouclierTaux = 0, int _visibilite = 0, int _attaque = 10);

        // getters
        int getVie() const;
        int getVieMax() const;
        int getBouclier() const;
        int getBouclierMax() const;
        float getBouclierTaux() const;
        int getVisibilite() const;
        int getAttaque() const;

        // setters
        void setVie(int const _vie);
        void setVieMax(int const _vieMax);
        int setBouclier(int const _bouclier);
        void setBouclierMax(int const _bouclierMax);
        void setBouclierTaux(float const _bouclierTaux);
        void setVisibilite(int const _visibilite);
        void setAttaque(int const _attaque);

        // autres
        void modifierVie(int const valeur);
        static Structure cloner(Structure const& modele, TechnologieStructure techS);


    protected:
		static int taille;
        int vie;
        int vieMax;
        int bouclier;
        int bouclierMax;
        float bouclierTaux;
        int visibilite;
        int attaque;
	
	private:
		friend std::ostream& operator<< (std::ostream& fluxSortant, Structure const& Structure);

};

typedef std::shared_ptr<Structure> StructurePtr;

#endif // STRUCTURE_HPP
