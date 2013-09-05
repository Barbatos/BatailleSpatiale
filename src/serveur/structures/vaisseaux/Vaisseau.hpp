#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP

#include "../../../global.hpp"
#include "../Structure.hpp"
#include "TechnologieVaisseau.hpp"

/*
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Vaisseau : public Structure {

    public:
        Vaisseau();
        Vaisseau(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int energieMax, int consommationMax);
        // Getters
        int getEnergie() const;
        int getEnergieMax() const;
        int getConsommationMax() const;
        // Setters
        void setEnergie(int const energie);
        void setEnergieMax(int const energieMax);
        void setConsommationMax(int const consommationMax);

        void modifierEnergie(int const valeur);
        static Vaisseau cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV);

        void afficher(std::ostream& fluxSortant) const;

    private:
        int energie;
        int energieMax;
        int consommationMax;

};

std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);

#endif // VAISSEAU_HPP

