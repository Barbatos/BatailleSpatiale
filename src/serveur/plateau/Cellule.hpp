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
class Cellule {

public:
    Cellule(EvenementPtr _evenement = 0, TypeCellule _type = CelluleVide);
    TypeCellule getType() const;
    
    bool possedeEvenement() const;
    bool possedeBatiment() const;
    bool possedeVaisseau() const;
    bool possedeEmplacement(TypeCellule _type) const;
    
    TypeCellule statutEmplacement() const;
    void setType(TypeCellule _type);
    
    int getCoutDeplacement() const;
    
    //void subir(Structure const& attaquant);
    Structure getAttaquant();
    TypeBatiment typeBatiment() const;
    bool estAccessible() const;
    
    BatimentPtr getBatiment();
    
    EvenementPtr getEvenement();
    
    void retirerVaisseau();
    void setVaisseau(VaisseauPtr _vaisseau);
    VaisseauPtr getVaisseau();
    int distanceMaximale() const;

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
