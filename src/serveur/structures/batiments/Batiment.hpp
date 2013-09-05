#ifndef BATIMENT_HPP
#define BATIMENT_HPP

#include "../../../global.hpp"
#include "../vaisseaux/Vaisseau.hpp"


/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments.
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


