#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "../vaisseaux/Vaisseau.hpp"
#include "TypeBatiment.hpp"
#include <memory>

class Vaisseau;

/*
* Classe qui d�finit les differents attributs
* que poss�dent les batiments.
*/

class Batiment : public Structure {

    public:
                Batiment();
                Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, TypeBatiment _type = BatimentVide);
                TypeBatiment getType() const;
                int getNiveau();
                void setNiveau(int niveau);
                void subir(Vaisseau const& attaquant);
                void subir(Batiment const& attaquant);

        protected:
                TypeBatiment type;
    private:
                int niveau;
};

typedef std::shared_ptr<Batiment> BatimentPtr;

#endif // BATIMENT_HPP
