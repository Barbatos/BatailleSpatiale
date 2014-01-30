#ifndef VAISSEAUSERVEUR_HPP
#define VAISSEAUSERVEUR_HPP
#include "../Structure.hpp"
#include "../batiments/BatimentServeur.hpp"
#include "TechnologieVaisseau.hpp"
#include "../../../commun/enum/TypeVaisseau.hpp"
#include <memory>

class BatimentServeur;
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
        sf::Int32 _vieMax,
        sf::Int32 _bouclierMax,
        float _bouclierTaux,
        sf::Int32 _visibilite,
        sf::Int32 _attaque,
        sf::Int32 _rayonAttaque,
        sf::Int32 _distanceMax,
        sf::Int32 _consommation,
        sf::Int32 _prixEnergie,
        sf::Int32 _prixMateriaux,
        TypeVaisseau _type = TypeVaisseau::Inexistant
    );

    // Getters
    sf::Int32 getConsommation() const;
    sf::Int32 distanceMaximale(sf::Int32 energie) const;
    sf::Int32 getDistanceMax() const;
    TypeVaisseau getType() const;

    // Setters
    void setConsommation(const sf::Int32 _consommation);
    
    static VaisseauServeur cloner(VaisseauServeur const& modele, TechnologieStructure techS, TechnologieVaisseau techV);
    int triangulaire(VaisseauServeurPtr vAttaquant);
    void afficher(std::ostream& fluxSortant) const;

protected:

private:
    TypeVaisseau type;
    sf::Int32 distanceMax;
    sf::Int32 consommation;

    friend std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);
    friend sf::Packet& operator <<(sf::Packet& paquet, const VaisseauServeur& vaisseau);
};

sf::Packet& operator <<(sf::Packet& paquet, const VaisseauServeur& vaisseau);

#endif // VAISSEAUSERVEUR_HPP

