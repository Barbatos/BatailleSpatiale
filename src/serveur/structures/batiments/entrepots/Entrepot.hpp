#ifndef ENTREPOT_HPP
#define ENTREPOT_HPP

#include "../Batiment.hpp"
/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments.
 */
class Entrepot : public Batiment {

    public:
    Entrepot(int _energie = 0, int _energieMax = 100);
    // Entrepot(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, int energieMax);

    int getEnergie();
    int ajouterEnergie(int ajout);
    int retirerEnergie(int retrait);
    void setEnergie(int _energie);

    int getEnergieMax();
    void setEnergieMax(int _energieMax);

    private:
    int energie;
    int energieMax;

};


#endif // ENTREPOT_HPP

