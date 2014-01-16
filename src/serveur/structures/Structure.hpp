#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#include "TechnologieStructure.hpp"
#include <SFML/System.hpp>
#include <memory>

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments et les vaisseaux.
 * Les classes Vaisseau et Batiment en héritent
 */

class Structure {

public:

    Structure(sf::Int32 _vieMax = 100, sf::Int32 _bouclierMax = 0, double _bouclierTaux = 0, sf::Int32 _visibilite = 0, sf::Int32 _attaque = 10);

    // Getter
    sf::Int32 getVie() const;
    sf::Int32 getVieMax() const;
    sf::Int32 getBouclier() const;
    sf::Int32 getBouclierMax() const;
    double getBouclierTaux() const;
    sf::Int32 getVisibilite() const;
    sf::Int32 getAttaque() const;

    // Setter
    void setVie( sf::Int32 const _vie);
    sf::Int32  setBouclier(sf::Int32 const _bouclier);
    void setVieMax( sf::Int32 const _vieMax);
    void setBouclierMax( sf::Int32 const _bouclierMax);
    void setBouclierTaux(double const _bouclierTaux);
    void setVisibilite( sf::Int32 const _visibilite);
    void setAttaque( sf::Int32 const _attaque);

    void subir(Structure const& attaquant);
    void attaquer(Structure& cible) const;
    void modifierVie(sf::Int32 const valeur);
    static Structure cloner(Structure const& modele, TechnologieStructure techS);


protected:
    sf::Int32 vie;
    sf::Int32 vieMax;
    sf::Int32 bouclier;
    sf::Int32 bouclierMax;
    double bouclierTaux;
    sf::Int32 visibilite;
    sf::Int32 attaque;

private:
    friend std::ostream& operator<< (std::ostream& fluxSortant, Structure const& Structure);

};

typedef std::shared_ptr<Structure> StructurePtr;

#endif // STRUCTURE_HPP
