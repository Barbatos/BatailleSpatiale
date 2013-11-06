#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "Structure.hpp"
#include "Batiment.hpp"
#include "TechnologieVaisseau.hpp"
#include "TypeVaisseau.hpp"
#include <memory>

/*
* Classe qui définit les differents attributs
* que possèdent les vaisseaux.
*/
class Vaisseau : public Structure {

    public:
        Vaisseau();
        Vaisseau(
            int vieMax,
            int bouclierMax,
            float bouclierTaux,
            int visibilite,
            int attaque,
            int _energieMax,
            int consommationMax ,
            TypeVaisseau _type = VaisseauVide
        );

        // Getters
        int getEnergie() const;
        int getEnergieMax() const;
        int getConsommationMax() const;
        const int distanceMaximale();
        const TypeVaisseau getType();

        // Setters
        void setEnergie(int const energie);
        void setEnergieMax(int const energieMax);
        void setConsommationMax(int const consommationMax);

        void modifierEnergie(int const valeur);
        static Vaisseau cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV);
        void subir(Vaisseau const& attaquant);
       // void subir(Batiment const& attaquant);
        void afficher(std::ostream& fluxSortant) const;

        protected:
                TypeVaisseau type;

    private:
        int energie;
        int energieMax;
        int consommationMax;
        TypeVaisseau _type;
        friend std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);

};

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP
