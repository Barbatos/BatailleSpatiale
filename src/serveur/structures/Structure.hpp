#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#include "TechnologieStructure.hpp"
#include <memory>
#include <SFML/System.hpp>

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments et les vaisseaux.
 * Les classes Vaisseau et Batiment en héritent
 */

class Structure {

public:

    Structure(sf::Int32 _vieMax = 100, sf::Int32 _bouclierMax = 0, float _bouclierTaux = 0, sf::Int32 _visibilite = 0, sf::Int32 _attaque = 10, sf::Int32 rayonAttaque = 0, sf::Int32 _prixEnergie = 0, sf::Int32 _prixMateriaux = 0);

    // Getter
    sf::Int32 getVie() const;
    sf::Int32 getVieMax() const;
    sf::Int32 getBouclier() const;
    sf::Int32 getBouclierMax() const;
    float getBouclierTaux() const;
    sf::Int32 getVisibilite() const;
    sf::Int32 getAttaque() const;
    sf::Int32 getPrixMateriaux() const;
    sf::Int32 getPrixEnergie() const;
    sf::Int32 getRayonAttaque() const;
    sf::Int32 getIdJoueur();
    void setIdJoueur( sf::Int32 const _id);

    // Setter
    void setVie( sf::Int32 const _vie);
    sf::Int32  setBouclier(sf::Int32 const _bouclier);
    void setVieMax( sf::Int32 const _vieMax);
    void setBouclierMax( sf::Int32 const _bouclierMax);
    void setBouclierTaux(float const _bouclierTaux);
    void setVisibilite( sf::Int32 const _visibilite);
    void setAttaque( sf::Int32 const _attaque);
    void setPrixMateriaux( sf::Int32 const _prix);
    void setPrixEnergie( sf::Int32 const _prix);
    void setRayonAttaque( sf::Int32 const _rayonAttaque);
    void subir(Structure const& attaquant);
    void attaquer(Structure& cible) const;
    void modifierVie(sf::Int32 const valeur);
    void setIdJoueur( sf::Int32 const _id);
    static Structure cloner(Structure const& modele, TechnologieStructure techS);


protected:
    static int taille;
    sf::Int32 vie;
    sf::Int32 vieMax;
    sf::Int32 bouclier;
    sf::Int32 bouclierMax;
    float bouclierTaux;
    sf::Int32 visibilite;
    sf::Int32 attaque;
    sf::Int32 rayonAttaque;
    sf::Int32 prixEnergie;
    sf::Int32 prixMateriaux;
    sf::Uint16 idJoueur;

private:
    friend std::ostream& operator<< (std::ostream& fluxSortant, Structure const& Structure);

};

typedef std::shared_ptr<Structure> StructurePtr;

#endif // STRUCTURE_HPP
