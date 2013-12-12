#ifndef BATIMENTSERVEUR_HPP
#define BATIMENTSERVEUR_HPP
#include "../vaisseaux/VaisseauServeur.hpp"
#include "../../../commun/enum/TypeBatiment.hpp"
#include <memory>

class VaisseauServeur;

/*
* Classe qui définit les differents attributs
* que possèdent les batiments.
*/

class BatimentServeur : public Structure {

public:
    BatimentServeur();
    BatimentServeur(sf::Int16 vieMax, sf::Int16 bouclierMax, float bouclierTaux, sf::Int16 visibilite, sf::Int16 attaque, sf::Int16 niveau, TypeBatiment _type = TypeBatiment::Inexistant);
    TypeBatiment getType() const;
    sf::Int16 getNiveau();
    void setNiveau(sf::Int16 niveau);
    void subir(VaisseauServeur const& attaquant);
    void subir(BatimentServeur const& attaquant);

protected:

private:
    TypeBatiment type;
    sf::Int16 niveau;

    friend sf::Packet& operator <<(sf::Packet& paquet, const BatimentServeur& batiment);
};

sf::Packet& operator <<(sf::Packet& paquet, const BatimentServeur& batiment);

typedef std::shared_ptr<BatimentServeur> BatimentServeurPtr;

#endif // BATIMENTSERVEUR_HPP
