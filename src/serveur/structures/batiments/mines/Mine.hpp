#ifndef MINE_HPP
#define MINE_HPP


#include "../Batiment.hpp"
#include "../entrepots/Entrepot.hpp"

/*
 * Classe qui d�finit les differents attributs
 * que poss�dent les batiments.
 */
class Mine : public Batiment {

    public:
    Mine();
    Mine(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, int production);

    int getProduction();
    void setProduction(int production);

    void ajouterEntrepot(Entrepot entrepot);
    void retirerEntrepot();


    private:
    int production;
    std::vector<Entrepot> listeEntrepot;


};



#endif // MINE_HPP
