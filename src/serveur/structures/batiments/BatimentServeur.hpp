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
    BatimentServeur(
        sf::Int32 vieMax,
        sf::Int32 bouclierMax,
        float bouclierTaux,
        sf::Int32 visibilite,
        sf::Int32 attaque,
        sf::Int32 niveau,
        sf::Int32 rayonAttaque,
        sf::Int32 prixEnergie,
        sf::Int32 prixMateriaux,
        TypeBatiment _type = TypeBatiment::Inexistant
    );
    TypeBatiment getType() const;
    sf::Int32 getNiveau();
    void setNiveau(sf::Int32 niveau);
    void subir(VaisseauServeur const& attaquant);
    void subir(BatimentServeur const& attaquant);

protected:

private:
    TypeBatiment type;
    sf::Int32 niveau;

    friend sf::Packet& operator <<(sf::Packet& paquet, const BatimentServeur& batiment);
};

sf::Packet& operator <<(sf::Packet& paquet, const BatimentServeur& batiment);

typedef std::shared_ptr<BatimentServeur> BatimentServeurPtr;

#endif // BATIMENTSERVEUR_HPP

