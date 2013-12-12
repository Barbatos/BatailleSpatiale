#ifndef CONSTRUCTEUR_HPP
#define CONSTRUCTEUR_HPP

#include "../../../../global.hpp"
#include "../../batiments/Batiment.hpp"



/*
 * Classe qui d�finit les differents attributs
 * que poss�dent les constructeurs.
 */
class Constructeur : public VaisseauServeur {

    public:
    Constructeur();
    Constructeur(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int energieMax, int consommationMax, int materiauxMax);

    int getMateriaux();
    void setMateriaux(int materiaux);
    int getMateriauxMax();
    void setMateriauxMax(int materiauxMax);
    void ajouterBatiment(Batiment batiment);
    void retirerBatiment();

    private:
    int materiaux;
    int materiauxMax;
    std::vector<Batiment> listeConstruction;


};

std::ostream& operator<<(std::ostream& fluxSortant, VaisseauServeur const& VaisseauServeur);

#endif // CONSTRUCTEUR_HPP

