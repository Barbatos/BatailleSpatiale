#ifndef VAISSEAUSERVEUR_HPP
#define VAISSEAUSERVEUR_HPP
#include "../Structure.hpp"
#include "../batiments/Batiment.hpp"
#include "TechnologieVaisseau.hpp"
#include "../../../commun/enum/TypeVaisseau.hpp"
#include <memory>

class Batiment;
class VaisseauServeur;

typedef std::shared_ptr<VaisseauServeur> VaisseauServeurPtr;


/*
* Classe qui définit les differents attributs
* que possèdent les vaisseaux.
*/
class VaisseauServeur : public Structure {

public:
    VaisseauServeur();
    VaisseauServeur(
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
    static VaisseauServeur cloner(VaisseauServeur const& modele, TechnologieStructure techS, TechnologieVaisseau techV);
    int triangulaire(VaisseauServeurPtr vAttaquant);
    void afficher(std::ostream& fluxSortant) const;

protected:

private:
    TypeVaisseau type;
    sf::Int16 distanceMax;
    sf::Int16 consommation;
    
    friend std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);
    friend sf::Packet& operator <<(sf::Packet& paquet, const VaisseauServeur& vaisseau);
};

sf::Packet& operator <<(sf::Packet& paquet, const VaisseauServeur& vaisseau);

#endif // VAISSEAUSERVEUR_HPP
