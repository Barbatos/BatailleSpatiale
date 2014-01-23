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
    Constructeur();
    Constructeur(sf::Int32 vieMax, sf::Int32 bouclierMax, float bouclierTaux, sf::Int32 visibilite, sf::Int32 attaque, sf::Int32 energieMax, sf::Int32 consommationMax, sf::Int32 rayonAttaque, sf::Int32 prixEnergie, sf::Int32 prixMateriaux);
    BatimentServeur getBatiment(int index);
    void ajouterBatiment(BatimentServeur batiment);
    void retirerBatiment();

    private:
    std::vector<BatimentServeur> listeConstruction;


};

std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);

#endif // CONSTRUCTEUR_HPP

