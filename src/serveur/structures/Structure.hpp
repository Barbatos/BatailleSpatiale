#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include "TechnologieStructure.hpp"

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments et les vaisseaux.
 * Les classes Vaisseau et Batiment en héritent
 */

class Structure{

    public:
        Structure(int _vieMax = 0, int _bouclierMax = 0, float _bouclierTaux = 0, int _visibilite = 0, int _attaque = 0);

        // Getter
        int getVie() const;
        int getVieMax() const;
        int getBouclier() const;
        int getBouclierMax() const;
        float getBouclierTaux() const;
        int getVisibilite() const;
        int getAttaque() const;

        // Setter
        void setVie( int const _vie);
        int  setBouclier(int const _bouclier);
        void setVieMax( int const _vieMax);
        void setBouclierMax( int const _bouclierMax);
        void setBouclierTaux(float const _bouclierTaux);
        void setVisibilite( int const _visibilite);
        void setAttaque( int const _attaque);

        void subir(Structure const& attaquant);
        void attaquer(Structure& cible) const;
        void modifierVie(int const valeur);
        static Structure cloner(Structure const& modele, TechnologieStructure techS);

        void afficher(std::ostream& fluxSortant) const;


    protected:
        int vie;
        int vieMax;
        int bouclier;
        int bouclierMax;
        float bouclierTaux;
        int visibilite;
        int attaque;

};

std::ostream& operator<<(std::ostream& fluxSortant, Structure const& Structure);

#endif // STRUCTURE_HPP
