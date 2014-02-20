#ifndef CONSTRUCTEUR_HPP
#define CONSTRUCTEUR_HPP

#include "../../../../global.hpp"
#include "../../batiments/BatimentServeur.hpp"




/*
 * Classe qui définit les differents attributs
 * que possèdent les constructeurs.
 */
class Constructeur : public VaisseauServeur {

public:
    Constructeur(sf::Int32 vieMax = 100, sf::Int32 bouclierMax = 100, float bouclierTaux = 0.3f, sf::Int32 visibilite = 100, sf::Int32 attaque = 100, sf::Int32 energieMax = 200, sf::Int32 consommationMax = 100, sf::Int32 rayonAttaque = 100, sf::Int32 prixEnergie = 500, sf::Int32 prixMateriaux = 1000);
    BatimentServeur getBatiment(int index);
    void ajouterBatiment(BatimentServeur batiment);
    void retirerBatiment();
    std::vector<BatimentServeur>* getListeConstruction();

private:
    std::vector<BatimentServeur> listeConstruction;
};

std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);

#endif // CONSTRUCTEUR_HPP
