#ifndef CELLULE_HPP
#define CELLULE_HPP
#include "../../commun/enum/TypeCellule.hpp"
#include "evenement/Evenement.hpp"
#include "../../commun/enum/TypeBatiment.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"
#include "../structures/Structure.hpp"

/**
 * Cette classe est une case elementaire du plateau
 */
class Cellule {

public:
    Cellule(EvenementPtr _evenement = 0, TypeCellule _type = TypeCellule::Vide);
    TypeCellule getType() const;
    
    bool possedeEvenement() const;
    bool possedeBatiment() const;
    bool possedeVaisseau() const;
    bool possedeEmplacement(TypeCellule _type) const;
    
    TypeCellule statutEmplacement() const;
    void setType(TypeCellule _type);
    
    /**
     * \brief Retourne le cout de déplacement dans la cellule
     * Si un vaisseau veut passer a travers cette cellule quel est 
     * le facteur du cout de deplacement ici?
     * 
     *  \return Le cout de deplacement
     */
    int getCoutDeplacement() const;
    
    //void subir(Structure const& attaquant);
    Structure getAttaquant();
    TypeBatiment typeBatiment() const;
    bool estAccessible() const;
    
    BatimentPtr getBatiment() const;
    
    EvenementPtr getEvenement() const;
    
    void retirerVaisseau();
    void setVaisseau(VaisseauPtr _vaisseau);
    VaisseauPtr getVaisseau() const;
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

sf::Packet& operator <<(sf::Packet& paquet, const Cellule& cellule);

#endif // CELLULE_HPP
