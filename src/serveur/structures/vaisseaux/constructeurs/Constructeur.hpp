#ifndef CONSTRUCTEUR_HPP
#define CONSTRUCTEUR_HPP

#include "../../batiments/Batiment.hpp"



/*
 * Classe qui définit les differents attributs
 * que possèdent les constructeurs.
 */
class Constructeur : public Vaisseau {

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

std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau);

#endif // CONSTRUCTEUR_HPP

