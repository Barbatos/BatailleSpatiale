#ifndef CELLULE_HPP
#define CELLULE_HPP
#include "TypeCellule.hpp"
#include "evenement/Evenement.hpp"
#include "../structures/batiments/TypeBatiment.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"
#include "../structures/Structure.hpp"

/**
 * Cette classe est une case elementaire du plateau
 */
class Cellule{
    
    public:
        Cellule(EvenementPtr _evenement = 0, TypeCellule _type = CelluleVide);
        TypeCellule getType() const;
        void setType(TypeCellule _type);
        bool possedeEvenement() const;
        bool possedeEmplacement(TypeCellule _type) const;
        TypeCellule statutEmplacement() const;
        int getCoutDeplacement() const;
        //void subir(Structure const& attaquant);
        Structure getAttaquant();
        TypeBatiment typeBatiment() const;
        int distanceMaximale() const;
        bool estAccessible() const;
        void retirerVaisseau();
        VaisseauPtr getVaisseau();
        void setVaisseau(VaisseauPtr _vaisseau);
        
        //Multiple fonctions de test
        void creerVaisseauTest();
        void creerVaisseauConstructeurTest();
        void creerBatimentBaseTest();
        
    protected:
        
    private:
        EvenementPtr evenement;
        BatimentPtr batiment;
        VaisseauPtr vaisseau;
        TypeCellule type;

};

#endif // CELLULE_HPP
