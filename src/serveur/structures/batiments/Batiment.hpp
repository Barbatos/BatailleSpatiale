#ifndef BATIMENT_HPP
#define BATIMENT_HPP

#include "../../../global.hpp"
#include "../vaisseaux/Vaisseau.hpp"


/*
 * Classe qui d�finit les differents attributs
 * que poss�dent les batiments.
 */
class Batiment : public Structure {

    public:
    Batiment();
    Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau);

    int getNiveau();
    void setNiveau(int niveau);

    private:
    int niveau;


};


#endif // BATIMENT_HPP


