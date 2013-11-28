#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "../Structure.hpp"
#include "../batiments/Batiment.hpp"
#include "TechnologieVaisseau.hpp"
#include "../../../commun/enum/TypeVaisseau.hpp"
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
        sf::Int16 _vieMax,
        sf::Int16 _bouclierMax,
        float _bouclierTaux,
        sf::Int16 _visibilite,
        sf::Int16 _attaque,
        sf::Int16 _distanceMax,
        sf::Int16 _consommation,
        TypeVaisseau _type = TypeVaisseau::Inexistant
    );

    // Getters
    sf::Int16 getConsommation() const;
    sf::Int16 getDistanceMax() const;
    TypeVaisseau getType() const;

    // Setters
    void setConsommation(const sf::Int16 _consommation);

    void modifierEnergie(sf::Int16 const valeur);
    static Vaisseau cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV);
    void subir(Vaisseau const& attaquant);
    void subir(Batiment const& attaquant);
    void afficher(std::ostream& fluxSortant) const;

protected:

private:
    TypeVaisseau type;
    sf::Int16 distanceMax;
    sf::Int16 consommation;
    
    friend std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);
    friend sf::Packet& operator <<(sf::Packet& paquet, const Vaisseau& vaisseau);
};

sf::Packet& operator <<(sf::Packet& paquet, const Vaisseau& vaisseau);

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP
