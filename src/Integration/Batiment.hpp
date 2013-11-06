#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "Vaisseau.hpp"
#include "TypeBatiment.hpp"
#include <memory>

/*
* Classe qui définit les differents attributs
* que possèdent les batiments.
*/

class Batiment : public Structure {

    public:
                Batiment();
                Batiment(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, TypeBatiment _type = BatimentVide);
                const TypeBatiment getType();
                int getNiveau();
                void setNiveau(int niveau);
             //   void subir(Vaisseau const& attaquant);
                void subir(Batiment const& attaquant);

        protected:
                TypeBatiment type;
    private:
                int niveau;
};

typedef std::shared_ptr<Batiment> BatimentPtr;

#endif // BATIMENT_HPP
