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
    Constructeur(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int energieMax, int consommationMax, int materiauxMax);

    int getMateriaux();
    void setMateriaux(int materiaux);
    int getMateriauxMax();
    void setMateriauxMax(int materiauxMax);
    void ajouterBatiment(BatimentServeur batiment);
    void retirerBatiment();

    private:
    int materiaux;
    int materiauxMax;
    std::vector<BatimentServeur> listeConstruction;


};

std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);

#endif // CONSTRUCTEUR_HPP

