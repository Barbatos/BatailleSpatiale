#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "../vaisseaux/Vaisseau.hpp"
#include "../../../commun/enum/TypeBatiment.hpp"
#include <memory>

class Vaisseau;

/*
* Classe qui définit les differents attributs
* que possèdent les batiments.
*/

class Batiment : public Structure {

public:
    Batiment();
    Batiment(sf::Int16 vieMax, sf::Int16 bouclierMax, float bouclierTaux, sf::Int16 visibilite, sf::Int16 attaque, sf::Int16 niveau, TypeBatiment _type = TypeBatiment::Inexistant);
    TypeBatiment getType() const;
    sf::Int16 getNiveau();
    void setNiveau(sf::Int16 niveau);
    void subir(Vaisseau const& attaquant);
    void subir(Batiment const& attaquant);

protected:

private:
    TypeBatiment type;
    sf::Int16 niveau;

    friend sf::Packet& operator <<(sf::Packet& paquet, const Batiment& batiment);
};

sf::Packet& operator <<(sf::Packet& paquet, const Batiment& batiment);

typedef std::shared_ptr<Batiment> BatimentPtr;

#endif // BATIMENT_HPP
