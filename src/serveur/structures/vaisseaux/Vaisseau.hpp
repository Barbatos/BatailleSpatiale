#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "../Structure.hpp"
#include "../batiments/Batiment.hpp"
#include "TechnologieVaisseau.hpp"
#include "TypeVaisseau.hpp"
#include <memory>

class Batiment;

/*
* Classe qui définit les differents attributs
* que possèdent les vaisseaux.
*/
class Vaisseau : public Structure {

public:
    Vaisseau();
    Vaisseau(
        int _vieMax,
        int _bouclierMax,
        float _bouclierTaux,
        int _visibilite,
        int _attaque,
        int _distanceMax,
        int _consommation,
        TypeVaisseau _type = VaisseauVide
    );

    // Getters
    int getConsommation() const;
    int getDistanceMax() const;
    TypeVaisseau getType() const;

    // Setters
    void setConsommation(const int _consommation);

    void modifierEnergie(int const valeur);
    static Vaisseau cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV);
    void subir(Vaisseau const& attaquant);
    void subir(Batiment const& attaquant);
    void afficher(std::ostream& fluxSortant) const;

protected:
    TypeVaisseau type;

private:
    int distanceMax;
    int consommation;
    TypeVaisseau _type;
    friend std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);

};

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP
