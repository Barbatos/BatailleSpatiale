#ifndef BATIMENTENERGIESERVEUR_HPP
#define BATIMENTENERGIESERVEUR_HPP
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeBatiment.hpp"
#include "BatimentServeur.hpp"

class BatimentEnergieServeur : public BatimentServeur {

public:
    BatimentEnergieServeur(
        sf::Int32 vieMax,
        sf::Int32 bouclierMax,
        float bouclierTaux,
        sf::Int32 visibilite,
        sf::Int32 attaque,
        sf::Int32 niveau,
        sf::Int32 rayonAttaque,
        sf::Int32 prixEnergie,
        sf::Int32 prixMateriaux,
        sf::Int32 _energieARecolter,
        TypeBatiment _type = TypeBatiment::Inexistant
    );
    void setEnergieARecolter(const sf::Int32& energieARecolter);
    const sf::Int32& getEnergieARecolter() const;

protected:

private:
    sf::Int32 energieARecolter;

    friend sf::Packet& operator <<(sf::Packet& paquet, const BatimentEnergieServeur& batiment);
};

sf::Packet& operator <<(sf::Packet& paquet, const BatimentEnergieServeur& batiment);

#endif // BATIMENTSERVEUR_HPP
