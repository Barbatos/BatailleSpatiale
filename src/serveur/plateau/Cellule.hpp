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
        // constructeur
        Cellule(EvenementPtr _evenement = 0, TypeCellule _type = CelluleVide);
        
        // getters
        TypeCellule getType() const;
        int getCoutDeplacement() const;
        Structure getAttaquant();
        VaisseauPtr getVaisseau();
        BatimentPtr getBatiment();
        int getAttaqueCellule();
    
        // Setters
        void setType(TypeCellule _type);
        void setVaisseau(VaisseauPtr _vaisseau);
        bool possedeEvenement() const;
    
        // autres
        bool possedeEmplacement(TypeCellule _type) const;
        TypeCellule statutEmplacement() const;
        TypeBatiment typeBatiment() const;
        int distanceMaximale() const;
        bool estAccessible() const;
        void retirerVaisseau();
        void attaquer(Cellule& cible) const;
        void subirDegat(Cellule cAttaquant);
        int degatTriangleVaisseauVaisseau(VaisseauPtr vAttaquant);
    
        // méthodes "tests"
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
