#ifndef CELLULESERVEUR_HPP
#define CELLULESERVEUR_HPP
#include "../../commun/enum/TypeCellule.hpp"
#include "evenement/Evenement.hpp"
#include "../../commun/enum/TypeBatiment.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"
#include "../structures/Structure.hpp"

/**
 * Cette classe est une case elementaire du plateau
 */
class CelluleServeur {

public:
    CelluleServeur(EvenementPtr _evenement = 0, TypeCellule _type = TypeCellule::Vide);
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
    
    BatimentServeurPtr getBatiment() const;
    
    EvenementPtr getEvenement() const;
    
    void retirerVaisseau();
    void setVaisseau(VaisseauServeurPtr _vaisseau);
    VaisseauServeurPtr getVaisseau() const;
    int distanceMaximale() const;

    //Multiple fonctions de test
    void creerVaisseauTest();
    void creerVaisseauConstructeurTest();
    void creerBatimentBaseTest();
    void attaquer(CelluleServeur *cCible);
    void defendre(int degat);

protected:

private:
    EvenementPtr evenement;
    BatimentServeurPtr batiment;
    VaisseauServeurPtr vaisseau;
    TypeCellule type;

};

sf::Packet& operator <<(sf::Packet& paquet, const CelluleServeur& cellule);

#endif // CELLULESERVEUR_HPP
